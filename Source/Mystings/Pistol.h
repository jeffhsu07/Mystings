// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class MYSTINGS_API APistol : public AWeapon
{
	GENERATED_BODY()
public:
    APistol();
    virtual void BeginPlay() override;
    virtual void Tick(float deltaTime) override;
    
    void OnStartFire();
    void OnStopFire();
    
    UAudioComponent* PlayWeaponSound(class USoundCue* Sound);
private:
    FTimerHandle WeaponTimer;
	
};
