// Fill out your copyright notice in the Description page of Project Settings.

#include "Mystings.h"
#include "TileManager.h"
#include "MystingsCharacter.h"
#include "MystingsPlayerController.h"

// Sets default values
ATileManager::ATileManager()
{
    // Create dummy root scene component
    DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
    RootComponent = DummyRoot;
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    // Set defaults
    BlockSpacing = 150.f;
    
    // Resize 2D array
    Tiles.SetNum(Rows, false);
    for(int32 X=0; X<Rows; X++) {
        Tiles[X].SetNum(Cols, false);
    }
}

TFunction<void (ATile*)> ATileManager::NOP() {
    return [=](ATile* tile) { 0; };
}


TFunction<void (ATile*)> ATileManager::Highlight() {
    return [=](ATile* tile) { if(tile) tile->Highlight(true, false); };
}

TFunction<void (ATile*)> ATileManager::Unhighlight() {
    return [=](ATile* tile) { if(tile) tile->Highlight(false, false); };
}

TFunction<void (ATile*)> ATileManager::Show() {
    return [=](ATile* tile) { if(tile) tile->SetActorHiddenInGame(false); };
}

TFunction<void (ATile*)> ATileManager::Hide() {
    return [=](ATile* tile) {
        if(tile) {
            tile->Highlight(false, true);
            tile->SetActorHiddenInGame(true);
        }
    };
}

TFunction<void (ATile*)> ATileManager::HighlightEnemies() {
    return [=](ATile* tile) {
        if(tile) {
            auto Enemy = tile->GetChar();
            auto Player = tile->GetManager()->GetPlayerChar();
            if(Enemy && Player) {
                if(Player->WeaponTrace(Enemy)) tile->SetActorHiddenInGame(false);
            }
        }
    };
}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
    Super::BeginPlay();
    
    // Loop to spawn each block
    for(int32 X=0; X<Rows; X++) {
        for(int32 Y=0; Y<Cols; Y++) {
            const float XOffset = X * BlockSpacing; // Divide by dimension
            const float YOffset = Y * BlockSpacing; // Modulo gives remainder
            
            // Make postion vector, offset from Grid location
            // Z is 5. to avoid collision with floor
            const FVector BlockLocation = FVector(XOffset, YOffset, 5.f) + GetActorLocation();
            
            // Spawn a block
            FActorSpawnParameters p;
            p.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
            ATile* NewTile = GetWorld()->SpawnActor<ATile>(BlockLocation, FRotator(0,0,0), p);
            
            if (NewTile != nullptr) {
                // Tell the block about its owner
                NewTile->TileManager = this;
                // Give x,y coordinates to tile
                NewTile->SetGridPos(FVector2D((float)X, (float)Y));
                // Set hidden
                NewTile->SetActorHiddenInGame(true);
            }
            
            Tiles[X][Y] = NewTile;
        }
    }
    
    // Setup neighbors and parents
    for(int32 X=0; X<Rows; X++) {
        for(int32 Y=0; Y<Cols; Y++) {
            auto curr = Tiles[X][Y];
            if(curr) {
                // Add neighboring nodes
                if(X != 0) {
                    if(Tiles[X-1][Y]) {
                        curr->AddNeighbor(Tiles[X-1][Y]);
                        Tiles[X-1][Y]->parent = curr;
                    }
                }
                if(X != Rows-1) {
                    if(Tiles[X+1][Y]) {
                        curr->AddNeighbor(Tiles[X+1][Y]);
                        Tiles[X+1][Y]->parent = curr;
                    }
                }
                if(Y != 0) {
                    if(Tiles[X][Y-1]) {
                        curr->AddNeighbor(Tiles[X][Y-1]);
                        Tiles[X][Y-1]->parent = curr;
                    }
                }
                if(Y != Cols-1) {
                    if(Tiles[X][Y+1]) {
                        curr->AddNeighbor(Tiles[X][Y+1]);
                        Tiles[X][Y+1]->parent = curr;
                    }
                }
            }
        }
    }
}

void ATileManager::ResetPathNodes()
{
    for (int32 X = 0; X < Rows; X++) {
        for (int32 Y = 0; Y < Cols; Y++) {
            if (Tiles[X][Y]) {
                auto curr = Tiles[X][Y];
                curr->f = 0; curr->h=0; curr->g=0;
                Tiles[X][Y]->bfsdist = -1;
            }
        }
    }
}

bool ATileManager::AStar(ATile* start, ATile* end, TFunction<void(ATile*)> modify) {
    TSet<ATile*> OpenSet;
    TSet<ATile*> ClosedSet;
    
    ResetPathNodes();
    
    // A* Search
    auto CurrentNode = start;
    ClosedSet.Emplace(CurrentNode);
    do {
        auto adj = CurrentNode->GetNeighbors();
        for(auto neighbor : adj) {
            if(ClosedSet.Contains(neighbor)) {
                continue;
            } else if(OpenSet.Contains(neighbor)) {
                float new_g = CurrentNode->g + 1.0f;
                if(new_g < neighbor->g) {
                    neighbor->parent = CurrentNode;
                    neighbor->g = new_g;
                    neighbor->f = neighbor->g + neighbor->h;
                }
            } else {
                neighbor->parent = CurrentNode;
                FVector2D dist = neighbor->GetGridPos() - end->GetGridPos();
                neighbor->h = FMath::Abs(dist.X) + FMath::Abs(dist.Y);
                neighbor->g = neighbor->parent->g + 1.0f;
                neighbor->f = neighbor->g + neighbor->h;
                if(!neighbor->IsBlocked()) {
                    OpenSet.Emplace(neighbor);
                } else {
                    if(neighbor->GetChar()->IsPlayer()) OpenSet.Emplace(neighbor);
                }
            }
        }
        
        if(OpenSet.Num() == 0) {
            break;
        }
        
        float min = -1.0f;
        for(auto n : OpenSet) {
            if (n->f < min || min == -1.0f) {
                min = n->f;
                CurrentNode = n;
            }
        }
        ClosedSet.Emplace(CurrentNode);
        OpenSet.Remove(CurrentNode);
        
    } while(CurrentNode != end);
    
    if(CurrentNode == end) {
        // Draw Path
        auto curr = end;
        while(curr != start) {
            modify(curr);
            curr = curr->parent;
        }
        modify(curr);
    }
    
    return (CurrentNode == end);
}

void ATileManager::BFS(ATile* root, int depth, TFunction<void(ATile*)> modify, bool bAddEnemies) {
    if(root) {
        ResetPathNodes();
        
        root->bfsdist = 0;
        TQueue<ATile*> q;
        q.Enqueue(root);
        
        int curr_depth = 0;
        while(!q.IsEmpty() || curr_depth <= depth) {
            ATile* curr;
            if(q.Dequeue(curr)) {
                // We have reached another layer
                if(curr->bfsdist > curr_depth) curr_depth++;
                // If the reached layer has exceeded our desired depth
                if(curr_depth > depth) {
                    break;
                } else {
                    modify(curr);
                    if(curr == root) curr->SetActorHiddenInGame(true);
                }
                
                auto adj = curr->GetNeighbors();
                for(auto& n : adj) {
                    if(n->bfsdist == -1 && (!n->IsBlocked() || bAddEnemies)) {
                        n->bfsdist = curr->bfsdist + 1;
                        n->parent = curr;
                        q.Enqueue(n);
                    }
                }
            }
        }
    }
}

void ATileManager::ShortestPath(ATile* start, ATile* end, TFunction<void(ATile*)> modify) {
    if(start != nullptr && end != nullptr) {
        // Draw Path
        auto curr = end;
        while(curr != start) {
            modify(curr);
            // Setup backtrack nodes for tiles (So we can allow actors to follow the path)
            curr->parent->backtrack = curr;
            curr = curr->parent;
        }
        //curr->parent->backtrack = curr;
        modify(curr);
    }
}


// Called every frame
void ATileManager::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
}

