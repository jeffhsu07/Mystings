// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>
#include "AIController.h"

#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYSTINGS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
    enum State {Start, Follow, Attack, Doing, Dead};
    
    void LoadLocations();
    void FollowPlayer();
    virtual void BeginPlay() override;
    virtual void Tick (float DeltaSeconds) override;
    void SetMyOwner(class AMystingsCharacter* owner) { MyOwner = owner; }
    
    void SetNewMoveDestination(const FVector DestLocation);
    void ExecuteMove();
private:
    class AMystingsCharacter* MyOwner;
    class AMystingsCharacter* PlayerChar;
    
    State state = Start;
};
