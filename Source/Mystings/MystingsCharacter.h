// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include <iostream>
#include "Tile.h"
#include "MystingsCharacter.generated.h"

UCLASS(Blueprintable)
class AMystingsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMystingsCharacter();

	// Called every frame.
    void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
    
    ATile* GetCurrentTile() { return CurrentTile; }
    ATile* GetOriginTile() { return OriginTile; }
    ATile* GetTilePosition() { return TilePosition; }
    void SetCurrentTile(ATile* tile);
    void SetTilePosition(ATile* tile) { TilePosition = tile; }
    
    void OnStartFire();
    void OnStopFire();
    
    void SetIsPlayer(bool player) { bIsPlayer = player; }
    UFUNCTION(BlueprintCallable,Category="IsPlayer")
    bool IsPlayer() { return bIsPlayer; }
    
    void SetNewMoveDestination(const FVector DestLocation);
    
    /** Navigates player to end tile */
    void FollowPath();
    
    void HasReached();
    bool GetReached() { return bHasReached; }
    void SetReached(bool reached) { bHasReached = reached; }
    
    bool IsMoving();
    
    bool WeaponTrace(AMystingsCharacter* Enemy);
    void AttackEnemy(AMystingsCharacter* Enemy);
    bool InRange(AMystingsCharacter* Enemy, int32 range);
    
    bool HasAttacked() { return bHasAttacked; }
    void SetHasAttacked(bool attacked) { bHasAttacked = attacked; }
    
    bool IsDead() { return bIsDead; }
    void SetDead(bool dead) { bIsDead = dead; }
    
    void PlayDeath();
    void Die();

    void MystingsTakeDamage(float damage);
    void MystingsHeal(float health);
    
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
protected:
    UPROPERTY(EditAnywhere, Category = Weapon)
    TSubclassOf<class AWeapon> WeaponClass;
    
    /** Tile at the origin of a turn. */
    class ATile* OriginTile = nullptr;
    /** Tile at the end of a turn. */
    class ATile* CurrentTile = nullptr;
    /** Move towards this tile. */
    class ATile* TilePosition = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
    float Health = 100.0f;
    
    UPROPERTY(EditDefaultsOnly)
    UAnimMontage* DeathAnim;
    
    FTimerHandle CharTimer;
    
    FTimerHandle ShootTimer;
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
    float ShootingTime = 1.2f;
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
    
    class APistol* MyPistol;
    
    bool bIsPlayer = false;
    bool bHasReached = false;
    
    bool bIsDead = false;
    
    bool bHasAttacked = false;
};

