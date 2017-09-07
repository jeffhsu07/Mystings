// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Mystings.h"
#include "Tile.h"
#include "TileManager.h"
#include "MystingsCharacter.h"
#include "MystingsPlayerController.h"
#include "MystingsGameMode.h"

#include <iostream>

ATile::ATile()
{
    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
        ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
        ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
        FConstructorStatics()
        : PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
        , BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
        , BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
        , OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;
    
    // Create dummy root scene component
    DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
    RootComponent = DummyRoot;
    
    // Create static mesh component
    BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
    BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
    BlockMesh->SetRelativeScale3D(FVector(0.5f,0.5f,0.05f)); // Was 0.25f for z
    BlockMesh->SetRelativeLocation(FVector(0.f,0.f,0.f)); // Was 0.25f for z
    BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
    BlockMesh->SetupAttachment(DummyRoot);
    // Disable collision for pawns
    BlockMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BlockMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    BlockMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
    
    BlockMesh->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnOverlapBegin);
    BlockMesh->OnComponentEndOverlap.AddDynamic(this, &ATile::OnOverlapEnd);
    
    // Save a pointer to the orange material
    BaseMaterial = ConstructorStatics.BaseMaterial.Get();
    BlueMaterial = ConstructorStatics.BlueMaterial.Get();
    OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
    
}

void ATile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Other Actor is the actor that triggered the event. Check that is not ourself.
    if ( (OtherActor != this) && ( OverlappedComp != nullptr ) )
    {
        AMystingsCharacter* Char = Cast<AMystingsCharacter>(OtherActor);
        if(Char) {
            SetChar(Char);
            
            if(Char->IsPlayer()) {
                if(!bHidden) HighlightClicked(true);
            }
            
            Char->SetTilePosition(this);
            if(Char->GetTilePosition() == Char->GetCurrentTile()) {
                Char->HasReached();
            }
        }
    }
}

void ATile::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // Other Actor is the actor that triggered the event. Check that is not ourself.
    if ( (OtherActor != this) && ( OverlappedComp != nullptr ) )
    {
        AMystingsCharacter* Char = Cast<AMystingsCharacter>(OtherActor);
        if(Char) {
            SetChar(nullptr);
        }
    }
}

void ATile::BeginPlay()
{
    Super::BeginPlay();
    
    TArray<AActor*> actors;
    GetOverlappingActors(actors);
    
    for(auto& actor : actors) {
        AMystingsCharacter* Char = Cast<AMystingsCharacter>(actor);
        if(Char) {
            Char->SetCurrentTile(this);
            auto gm = Cast<AMystingsGameMode>(GetWorld()->GetAuthGameMode());
            if(gm) gm->AddPlayer(Char);
            if(Char->IsPlayer() && TileManager) TileManager->SetPlayerChar(Char);
        }
    }
}

void ATile::HandleClicked()
{
    HighlightClicked(true);
    if (!bHidden) {
        auto controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
        if (controller) {
            AMystingsPlayerController* player = Cast<AMystingsPlayerController>(controller);
            if(player) {
                player->SetCurrentTile(this);
            }
        }
    }
}

void ATile::HighlightClicked(bool bOn)
{
    auto controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
    auto player = Cast<AMystingsPlayerController>(controller);
    // Check we are not already active
    if (!bIsActive && player)
    {
        if(player->GetCurrentTile() != nullptr) {
            bIsActive = true;
            
            // Change material
            if (bOn) BlockMesh->SetMaterial(0, OrangeMaterial);
            else BlockMesh->SetMaterial(0, BlueMaterial);
        }
    }
}

void ATile::HandleAttacked()
{
    HighlightClicked(true);
    if (!bHidden) {
        auto controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
        if (controller) {
            AMystingsPlayerController* player = Cast<AMystingsPlayerController>(controller);
            if(player) {
                if(this->GetChar()) player->AttackEnemy(this->GetChar());
            }
        }
    }
}

void ATile::AddNeighbor(ATile* tile)
{
    Adj.Add(tile);
}

void ATile::Highlight(bool bOn, bool bStrong)
{
    // Do not highlight if the block has already been activated.
    if (bIsActive && !bStrong)
    {
        return;
    }
    
    bIsActive = false;
    
    if (bOn)
    {
        BlockMesh->SetMaterial(0, BaseMaterial);
    }
    else
    {
        BlockMesh->SetMaterial(0, BlueMaterial);
    }
}
