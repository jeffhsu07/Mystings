// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "MystingsTurn.h"
#include "MystingsGameMode.generated.h"

UCLASS(minimalapi)
class AMystingsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMystingsGameMode();
    
    virtual void Tick(float DeltaSeconds) override;
    
    void AddPlayer(AMystingsCharacter* Char) { Turn.AddPlayer(Char); }
    UFUNCTION(BlueprintCallable, Category="MoveChar")
    void MoveChar();
    UFUNCTION(BlueprintCallable, Category="AttackChar")
    void AttackChar();
    UFUNCTION(BlueprintCallable, Category="HealChar")
    void HealChar();
    UFUNCTION(BlueprintCallable, Category="PlayerHasWon")
    bool PlayerHasWon();
private:
    MystingsTurn Turn;
    bool bMovementComplete = false;
};



