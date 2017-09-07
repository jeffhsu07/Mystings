// Fill out your copyright notice in the Description page of Project Settings.

#include "Mystings.h"
#include "EnemyAIController.h"

#include "Tile.h"
#include "MystingsCharacter.h"
#include "TileManager.h"

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();
    
    PlayerChar = Cast<AMystingsCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    
    MyOwner = Cast<AMystingsCharacter>(GetPawn());
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AEnemyAIController::ExecuteMove()
{
    if(MyOwner->InRange(PlayerChar, 6) && MyOwner->WeaponTrace(PlayerChar)) {
        MyOwner->AttackEnemy(PlayerChar);
    } else {
        FollowPlayer();
    }
}

void AEnemyAIController::FollowPlayer()
{
    ATile* Dest = MyOwner->GetCurrentTile();
    Dest->GetManager()->AStar(Dest, PlayerChar->GetCurrentTile(), ATileManager::NOP());
    Dest->GetManager()->ShortestPath(Dest, PlayerChar->GetCurrentTile(), ATileManager::NOP());
    
    // We can only move a maximum of 4 tiles per move
    for(int i = 0; i < 4; i++) {
        if(Dest->backtrack) {
            // If the next tile is the player, then don't move anymore
            if(Dest->backtrack->GetChar()) if(Dest->backtrack->GetChar()->IsPlayer()) break;
            Dest = Dest->backtrack;
        }
    }
    
    MyOwner->SetCurrentTile(Dest);
}

void AEnemyAIController::SetNewMoveDestination(const FVector DestLocation)
{
    if (MyOwner)
    {
        UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
        float const Distance = FVector::Dist(DestLocation, MyOwner->GetActorLocation());
        
        // We need to issue move command only if far enough in order for walk animation to play correctly
        if (NavSys && (Distance > 120.0f))
        {
            NavSys->SimpleMoveToLocation(this, DestLocation);
        }
    }
}
