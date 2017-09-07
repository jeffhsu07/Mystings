// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Mystings.h"
#include "MystingsCharacter.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Pistol.h"
#include "MystingsPlayerController.h"
#include "EnemyAIController.h"
#include "NavComponent.h"

AMystingsCharacter::AMystingsCharacter()
{
    //instantiate mypistol to null
    MyPistol = nullptr;
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

										  // Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMystingsCharacter::SetNewMoveDestination(const FVector DestLocation)
{
    if(AMystingsPlayerController* PC = Cast<AMystingsPlayerController>(GetController())) {
        PC->SetNewMoveDestination(DestLocation);
    } else {
        if(AEnemyAIController* AIC = Cast<AEnemyAIController>(GetController())) {
            AIC->SetNewMoveDestination(DestLocation);
        }
    }
}

void AMystingsCharacter::FollowPath()
{
    if(TilePosition != CurrentTile && CurrentTile != nullptr && TilePosition != nullptr) {
        if(TilePosition->backtrack) SetNewMoveDestination(TilePosition->backtrack->GetActorLocation());
    }
}

void AMystingsCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (WeaponClass)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;
            // Need to set rotation like this because otherwise gun points down
            FRotator Rotation(0.0f, 0.0f, -90.0f);
            // Spawn the Weapon
            MyPistol = World->SpawnActor<APistol>(WeaponClass, FVector::ZeroVector,
                                                  Rotation, SpawnParams);
            if (MyPistol)
            {
                // This is attached to "WeaponPoint" which is defined in the skeleton
                MyPistol->AttachToComponent(GetMesh(),
                                            FAttachmentTransformRules::KeepRelativeTransform,
                                            TEXT("WeaponPoint"));
                MyPistol->SetMyOwner(this);
            }
        }
    }
}

bool AMystingsCharacter::WeaponTrace(AMystingsCharacter* Enemy)
{
    return MyPistol->WeaponTrace(Enemy);
}

void AMystingsCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
    
    FollowPath();
}

void AMystingsCharacter::OnStartFire()
{
    if(MyPistol != nullptr) {
        MyPistol->OnStartFire();
    }
}

void AMystingsCharacter::OnStopFire()
{
    if(MyPistol != nullptr) {
        MyPistol->OnStopFire();
    }
    if (AMystingsPlayerController* PC = Cast<AMystingsPlayerController>(GetController())) {
        PC->FinishShooting();
    }
    bHasAttacked = true;
}

void AMystingsCharacter::HasReached()
{
    SetReached(true);
    if (AMystingsPlayerController* PC = Cast<AMystingsPlayerController>(GetController())) {
        PC->HasReached();
    }
}

bool AMystingsCharacter::IsMoving()
{
    return GetVelocity().Size() != 0;
}

void AMystingsCharacter::SetCurrentTile(ATile* tile)
{
    if(tile != nullptr) {
        // Spawn player at the location of closest tile
        if(CurrentTile == nullptr) {
            FVector pos = GetActorLocation();
            pos.X = tile->GetActorLocation().X;
            pos.Y = tile->GetActorLocation().Y;
            SetActorLocation(pos);
        }
        
        TilePosition = CurrentTile;
        OriginTile = CurrentTile;
        CurrentTile = tile;
        
        if(bIsPlayer) {
            CurrentTile->HighlightClicked(true);
        }
    }
}

void AMystingsCharacter::AttackEnemy(AMystingsCharacter* Enemy)
{
    if(Enemy) {
        FVector temp = Enemy->GetActorLocation() - this->GetActorLocation();
        temp.Z = 0.0f;
        temp.Normalize();
        this->SetActorRotation(temp.Rotation());
        
        Enemy->MystingsTakeDamage(MyPistol->GetDamage());
        
        this->OnStartFire();
        GetWorldTimerManager().SetTimer(ShootTimer, this, &AMystingsCharacter::OnStopFire, ShootingTime);
    }
}

void AMystingsCharacter::PlayDeath()
{
    float DestroyTime = PlayAnimMontage(DeathAnim)-0.25f;
    GetWorldTimerManager().SetTimer(CharTimer, this, &AMystingsCharacter::Die,
                                    DestroyTime);
}

void AMystingsCharacter::Die()
{
    GetMesh()->Deactivate();
}

bool AMystingsCharacter::InRange(AMystingsCharacter* Enemy, int32 range)
{
    FVector2D diff = this->GetCurrentTile()->GetGridPos() - Enemy->GetCurrentTile()->GetGridPos();
    int32 ManDis = FMath::Abs(diff.X) + FMath::Abs(diff.Y);
    return ManDis <= range;
}

void AMystingsCharacter::MystingsTakeDamage(float damage)
{
    Health -= damage;
}

void AMystingsCharacter::MystingsHeal(float health)
{
    Health += health;
}
