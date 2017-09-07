// Fill out your copyright notice in the Description page of Project Settings.

#include "Mystings.h"
#include "Weapon.h"
#include "Tile.h"
#include "MystingsCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}

bool AWeapon::WeaponTrace(AMystingsCharacter* Enemy) {
    static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
    static FName MuzzleSocket = FName(TEXT("MuzzleFlashSocket"));
    
    // Start from the muzzle's position
    //FVector StartPos = WeaponMesh->GetSocketLocation(MuzzleSocket);
    FVector StartPos = MyOwner->GetActorLocation();
    // Calculate end position
    FVector EndPos = Enemy->GetActorLocation();
    // Perform trace to retrieve hit info
    FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
    TraceParams.bTraceAsyncScene = true;
    TraceParams.bReturnPhysicalMaterial = true;
    // This fires the ray and checks against all objects w/ collision
    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos,
                                            FCollisionObjectQueryParams::AllObjects, TraceParams);
    // Did this hit anything?
    if (Hit.bBlockingHit)
    {
        //UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX, Hit.ImpactPoint);
        
        AMystingsCharacter* Char = Cast<AMystingsCharacter>(Hit.GetActor());
        if (Char == Enemy)
        {
            return true;
        }
    }
    
    return false;
}

