// Fill out your copyright notice in the Description page of Project Settings.

#include "Mystings.h"
#include "Pistol.h"
#include "MystingsCharacter.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "MystingsPlayerController.h"

APistol::APistol()
{
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;
    PrimaryActorTick.bCanEverTick = true;
    FireRate = 1.0f;
    WeaponRange = 4.0f;
    Damage = 10.0f;
}

void APistol::BeginPlay(){
    Super::BeginPlay();
}

void APistol::Tick(float deltaTime){
    Super::Tick(deltaTime);
}

void APistol::OnStartFire() {
    FireAC = PlayWeaponSound(FireLoopSound);

    MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, RootComponent);
    MuzzlePSC->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, TEXT("MuzzleFlashSocket"));
}

void APistol::OnStopFire() {
    //GetWorldTimerManager().ClearTimer(WeaponTimer);
    if(FireAC){
        FireAC->Stop();
    }
    if(MuzzlePSC){
        MuzzlePSC->DeactivateSystem();
    }
    PlayWeaponSound(FireFinishSound);
}

UAudioComponent* APistol::PlayWeaponSound(USoundCue* Sound)
{
    UAudioComponent* AC = NULL;
    if (Sound)
    {
        AC = UGameplayStatics::SpawnSoundAttached(Sound, RootComponent);
    }
    return AC;
}



