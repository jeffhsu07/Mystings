// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class MYSTINGS_API AWeapon : public AActor
{
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    AWeapon();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    bool WeaponTrace(class AMystingsCharacter* Enemy);
    
    void OnStopFire();
    void OnStartFire();

    void SetMyOwner(class AMystingsCharacter* owner){ MyOwner = owner; };
    class AMystingsCharacter* GetMyOwner() { return MyOwner; };
    UAudioComponent* PlayWeaponSound(class USoundCue* Sound);
    
    USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; };
    
    float GetDamage(){return Damage;}
    
protected:
    
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
    USkeletalMeshComponent* WeaponMesh;
    
    
    UPROPERTY(EditDefaultsOnly, Category = Sound)
    class USoundCue* FireLoopSound;
    
    UPROPERTY(EditDefaultsOnly, Category = Sound)
    class USoundCue* FireFinishSound;
    
    UPROPERTY(Transient)
    class UAudioComponent* FireAC;
    
    UPROPERTY(EditDefaultsOnly, Category = Effects)
    class UParticleSystem* MuzzleFX;
    
    UPROPERTY(EditDefaultsOnly, Category = Effects)
    class UParticleSystem* HitFX;
    
    UPROPERTY(Transient)
    class UParticleSystemComponent* MuzzlePSC;
    
    UPROPERTY(EditAnywhere)
    float FireRate;
    
    UPROPERTY(EditAnywhere)
    float WeaponRange;
    
    UPROPERTY(EditAnywhere)
    float Damage;
    
    class AMystingsCharacter* MyOwner;
    
    
};
