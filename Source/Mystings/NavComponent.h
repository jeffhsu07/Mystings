// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>
#include "Components/ActorComponent.h"
#include "Tile.h"
#include "NavComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTINGS_API UNavComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNavComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    void FollowPath(ATile* end);
    
    void SetCurrentTile(ATile* tile) { CurrNode = tile; }
private:
    ATile* CurrNode;
};
