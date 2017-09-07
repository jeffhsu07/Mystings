// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DwarfCharacter.generated.h"

UCLASS()
class MYSTINGS_API ADwarfCharacter : public ACharacter
{
    GENERATED_BODY()
    
public:
    // Sets default values for this character's properties
    ADwarfCharacter();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    UFUNCTION(BlueprintCallable,Category="DwarfDeath")
    void PlayDeathAnim();
    
    void DestroyDwarf();
protected:
    UPROPERTY(EditDefaultsOnly)
    UAnimMontage* DeathAnim;
    UPROPERTY(EditAnywhere, Category = Damage)
    float Health = 20.0f;
    
};
