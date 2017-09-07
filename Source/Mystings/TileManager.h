// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <iostream>
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "TileManager.generated.h"

UCLASS()
class MYSTINGS_API ATileManager : public AActor
{
    GENERATED_BODY()
    
    /** Dummy root component */
    UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* DummyRoot;
public:
    // Sets default values for this actor's properties
    ATileManager();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    /** Number of blocks */
    UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
    int32 Rows = 18;
    UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
    int32 Cols = 25;
    
    /** Spacing of blocks */
    UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
    float BlockSpacing;
    
    ATile* GetTile(int32 i, int32 j) { return Tiles[i][j]; }
    
    void ResetPathNodes();
    
    /** Pathfinding algorithms */
    void BFS(ATile* root, int depth, TFunction<void(ATile*)> modify, bool bAddEnemies);
    bool AStar(ATile* start, ATile* end, TFunction<void (ATile*)> modify);
    
    void ShortestPath(ATile* start, ATile* end, TFunction<void(ATile*)> modify);
    
    class AMystingsCharacter* GetPlayerChar() { return PlayerChar; }
    void SetPlayerChar(class AMystingsCharacter* Char) { PlayerChar = Char; }
    
    static TFunction<void (ATile*)> NOP();
    static TFunction<void (ATile*)> Highlight();
    static TFunction<void (ATile*)> Unhighlight();
    static TFunction<void (ATile*)> Show();
    static TFunction<void (ATile*)> Hide();
    static TFunction<void (ATile*)> HighlightEnemies();
private:
    // All of the tiles in the grid
    TArray<TArray<ATile*>> Tiles;
    
    ATile* Start;
    ATile* End;
    
    class AMystingsCharacter* PlayerChar;
};
