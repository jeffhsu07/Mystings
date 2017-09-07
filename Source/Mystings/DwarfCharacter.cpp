// Fill out your copyright notice in the Description page of Project Settings.

#include "Mystings.h"
#include "DwarfCharacter.h"


// Sets default values
ADwarfCharacter::ADwarfCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
}

// Called when the game starts or when spawned
void ADwarfCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ADwarfCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}

// Called to bind functionality to input
void ADwarfCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
    
}
void ADwarfCharacter::PlayDeathAnim(){
    float duration = PlayAnimMontage(DeathAnim);
    FTimerHandle DeathTimer;
    GetWorldTimerManager().SetTimer(DeathTimer, this, &ADwarfCharacter::DestroyDwarf,duration, false);
    
}
void ADwarfCharacter::DestroyDwarf(){
    Destroy();
}
