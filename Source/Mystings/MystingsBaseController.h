// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Controller.h"
#include "Tile.h"
#include "MystingsBaseController.generated.h"

/**
 * 
 */
UCLASS()
class AMystingsBaseController : public AController
{
	GENERATED_BODY()
public:
    AMystingsBaseController();
    
    ATile* GetCurrentTile() { return CurrentTile; }
    void SetCurrentTile(ATile* tile);
    
    void SetTilePosition(ATile* tile);
    /** Navigate player to the given world location. */
    void SetNewMoveDestination(const FVector DestLocation);
protected:
    // For weapon
    void OnStartFire();
    void OnStopFire();
    
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
    class ATile* CurrentBlockFocus;
    
    /** Tile at the end of a turn. */
    class ATile* CurrentTile = nullptr;
    
    /** Move towards this tile. */
    class ATile* TilePosition = nullptr;
};
