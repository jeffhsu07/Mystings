// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

/** A block that can be clicked */
UCLASS(minimalapi)
class ATile : public AActor
{
    GENERATED_BODY()
    
    /** Dummy root component */
    UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* DummyRoot;
    
    /** StaticMesh component for the clickable block */
    UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* BlockMesh;
    
public:
    ATile();
    
    /** Are we currently active? */
    bool bIsActive;
    
    /** Pointer to white material used on the focused block */
    UPROPERTY()
    class UMaterial* BaseMaterial;
    
    /** Pointer to blue material used on inactive blocks */
    UPROPERTY()
    class UMaterialInstance* BlueMaterial;
    
    /** Pointer to orange material used on active blocks */
    UPROPERTY()
    class UMaterialInstance* OrangeMaterial;
    
    /** Grid that owns us */
    UPROPERTY()
    class ATileManager* TileManager;
    ATileManager* GetManager() { return TileManager; }
    
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    void HandleClicked();
    void HandleAttacked();
    
    void Highlight(bool bOn, bool bStrong);
    void HighlightClicked(bool bOn);
    
    void AddNeighbor(ATile* tile);
    TArray<ATile*>& GetNeighbors() { return Adj; }
    
    // Use this to set/get the grid postiion of the tile
    // (You shouldn't have to call the set function yourself)
    void SetGridPos(const FVector2D& pos) { GridPos = pos; }
    const FVector2D& GetGridPos() const { return GridPos; }
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    bool IsBlocked() { return TileChar != nullptr; }
    
    // For A*
    ATile* parent = nullptr;
    float f = 0.0f;
    float g = 0.0f;
    float h = 0.0f;
    
    // For BFS
    int32 bfsdist = -1;
    // For Shortest Path
    ATile* backtrack = nullptr;
    
    // Setters and Getters for TileChar
    void SetChar(class AMystingsCharacter* curr) {  TileChar = curr; }
    class AMystingsCharacter* GetChar() { return TileChar; }
public:
    /** Returns DummyRoot subobject **/
    FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
    /** Returns BlockMesh subobject **/
    FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
private:
    FVector2D GridPos;
    // Neighbors of this tile
    TArray<ATile*> Adj;
    
    class AMystingsCharacter* TileChar;
};



