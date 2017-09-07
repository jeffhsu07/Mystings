// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "Tile.h"
#include "MystingsPlayerController.generated.h"

UCLASS()
class AMystingsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMystingsPlayerController();
    // Called every frame.
    void BeginPlay() override;

    /** Input handlers for SetDestination action. */
    void OnSetDestinationPressed();
    void OnSetDestinationReleased();
    
    /** Navigate player to the given world location. */
    void SetNewMoveDestination(const FVector DestLocation);
    
    ATile* GetCurrentTile();
    void SetCurrentTile(ATile* tile);
    
    void AttackEnemy(class AMystingsCharacter* tile);
    
    bool GetReached();
    void HasReached();
    bool IsMoving();
    
    bool IsAttacking() { return bIsAttacking; }
    void SetIsAttacking(bool attacking) { bIsAttacking = attacking; }
    
    void FinishShooting();
    
    ATile* GetEnemyTile();
    void UpdateMouseLook();
    
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

    /** Navigate player to the current mouse cursor location. */
    void MoveToMouseCursor();
    
    // Called on every tick
    void OnMouseHover();
    
    // For weapon
    void OnStartFire();
    void OnStopFire();
    
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
    class ATile* CurrentBlockFocus;
    
    class ATile* CurrentClickedTile = nullptr;
    
    bool bIsAttacking = false;
};


