// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Mystings.h"
#include "MystingsPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "MystingsCharacter.h"
#include "TileManager.h"

AMystingsPlayerController::AMystingsPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMystingsPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

    // Only allow the player to click/hover tiles if the player is not moving
    // and a tile hasn't already been clicked
    if(!IsMoving() && CurrentClickedTile == nullptr) {
        // keep updating the destination every tick while desired
        if (bMoveToMouseCursor)
        {
            MoveToMouseCursor();
            //OnSetDestinationReleased();
        }

        OnMouseHover();
    }
}

void AMystingsPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMystingsPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMystingsPlayerController::OnSetDestinationReleased);
}

void AMystingsPlayerController::MoveToMouseCursor()
{
    if(!IsMoving() && CurrentClickedTile == nullptr && !GetReached()) {
        // Trace to see what is under the mouse cursor
        FHitResult Hit;
        GetHitResultUnderCursor(ECC_Visibility, false, Hit);

        if (Hit.bBlockingHit)
        {
            if (Hit.Actor.IsValid())
            {
                ATile* HitBlock = Cast<ATile>(Hit.Actor.Get());
                if(HitBlock && !HitBlock->bHidden) {
                    if(bIsAttacking) {
                        HitBlock->HandleAttacked();
                    } else {
                        HitBlock->HandleClicked();
                    }
                    CurrentClickedTile = HitBlock;
                }
            }
        }
    }
}

void AMystingsPlayerController::AttackEnemy(AMystingsCharacter* Enemy)
{
    AMystingsCharacter* PlayerChar = Cast<AMystingsCharacter>(GetPawn());
    if(PlayerChar) PlayerChar->AttackEnemy(Enemy);
}

void AMystingsPlayerController::OnMouseHover()
{
    // Trace to see what is under the mouse cursor
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);
    if (Hit.Actor.IsValid()) {
        ATile* HitBlock = Cast<ATile>(Hit.Actor.Get());
        if (CurrentBlockFocus != HitBlock) {
            if(bIsAttacking) {
                if (CurrentBlockFocus) {
                    // Unhighlight previously highlighted block
                    CurrentBlockFocus->Highlight(false, false);
                }
                if (HitBlock) {
                    // Highlight selected block
                    HitBlock->Highlight(true, false);
                }
            } else {
                if (CurrentBlockFocus) {
                    // Unhighlight previously highlighted shortest-path blocks
                    auto TileManager = CurrentBlockFocus->GetManager();
                    if(!CurrentBlockFocus->bHidden && TileManager && GetCurrentTile()) {
                        TileManager->ShortestPath(GetCurrentTile(), CurrentBlockFocus, ATileManager::Unhighlight());
                    }
                }
                if (HitBlock) {
                    // Highlight shortest-path blocks
                    auto TileManager = HitBlock->GetManager();
                    if(!HitBlock->bHidden && TileManager && GetCurrentTile()) {
                        TileManager->ShortestPath(GetCurrentTile(), HitBlock, ATileManager::Highlight());
                    }
                }
            }
            CurrentBlockFocus = HitBlock;
        }
    }
}

ATile* AMystingsPlayerController::GetCurrentTile() {
    AMystingsCharacter* Char = Cast<AMystingsCharacter>(GetPawn());
    if(Char) return Char->GetCurrentTile();
    return nullptr;
}

bool AMystingsPlayerController::IsMoving() {
    AMystingsCharacter* Char = Cast<AMystingsCharacter>(GetPawn());
    if(Char) return Char->IsMoving();
    return true;
}

void AMystingsPlayerController::SetCurrentTile(ATile* tile) {
    AMystingsCharacter* Char = Cast<AMystingsCharacter>(GetPawn());
    if(Char) Char->SetCurrentTile(tile);
}

void AMystingsPlayerController::SetNewMoveDestination(const FVector DestLocation)
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

void AMystingsPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto Char = Cast<AMystingsCharacter>(GetPawn());
    if(Char) Char->SetIsPlayer(true);
}

bool AMystingsPlayerController::GetReached()
{
    auto Char = Cast<AMystingsCharacter>(GetPawn());
    if(Char) return Char->GetReached();
    return false;
}

void AMystingsPlayerController::HasReached()
{
    CurrentClickedTile = nullptr;
}

void AMystingsPlayerController::OnSetDestinationPressed()
{
	bMoveToMouseCursor = true;
}

void AMystingsPlayerController::OnSetDestinationReleased()
{
	bMoveToMouseCursor = false;
}

void AMystingsPlayerController::OnStartFire()
{
    Cast<AMystingsCharacter>(GetPawn())->OnStartFire();
}

void AMystingsPlayerController::OnStopFire()
{
    Cast<AMystingsCharacter>(GetPawn())->OnStopFire();
    FinishShooting();
}

void AMystingsPlayerController::FinishShooting()
{
    CurrentClickedTile = nullptr;
}

