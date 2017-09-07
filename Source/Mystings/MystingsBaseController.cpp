// Fill out your copyright notice in the Description page of Project Settings.

#include "Mystings.h"
#include "MystingsBaseController.h"
#include "MystingsCharacter.h"

AMystingsBaseController::AMystingsBaseController()
{

}

void AMystingsBaseController::SetCurrentTile(ATile* tile)
{
    // Spawn player at the location of closest tile
    if(CurrentTile == nullptr) {
        APawn* MyPawn = GetPawn();
        if(MyPawn) {
            FVector pos = MyPawn->GetActorLocation();
            pos.X = tile->GetActorLocation().X;
            pos.Y = tile->GetActorLocation().Y;
            MyPawn->SetActorLocation(pos);
        }
    }
    
    TilePosition = CurrentTile;
    CurrentTile = tile;
    CurrentTile->HighlightClicked(true);
}

void AMystingsBaseController::SetTilePosition(ATile* tile)
{
    TilePosition = tile;
}

void AMystingsBaseController::SetNewMoveDestination(const FVector DestLocation)
{
    APawn* const MyPawn = GetPawn();
    if (MyPawn)
    {
        UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
        float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
        
        // We need to issue move command only if far enough in order for walk animation to play correctly
        if (NavSys && (Distance > 120.0f))
        {
            NavSys->SimpleMoveToLocation(this, DestLocation);
        }
    }
}

void AMystingsBaseController::OnStartFire(){
    Cast<AMystingsCharacter>(GetPawn())->OnStartFire();
}

void AMystingsBaseController::OnStopFire(){
    Cast<AMystingsCharacter>(GetPawn())->OnStopFire();
}
