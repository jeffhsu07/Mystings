// Fill out your copyright notice in the Description page of Project Settings.

#include "Mystings.h"
#include "MystingsTurn.h"

#include "TileManager.h"
#include "MystingsCharacter.h"
#include "MystingsPlayerController.h"
#include "EnemyAIController.h"

MystingsTurn::MystingsTurn()
{
}

MystingsTurn::~MystingsTurn()
{
}

void MystingsTurn::AddPlayer(AMystingsCharacter* Char)
{
    if(Char->IsPlayer()) {
        Chars.EmplaceAt(0, Char);
    } else {
        Chars.Emplace(Char);
    }
}

bool MystingsTurn::IsValidMove()
{
    return (Movement != Doing) && (Attack != Doing) && (Heal != Doing);
}

void MystingsTurn::ResetButtons()
{
    Movement = Ready;
    Attack = Ready;
    Heal = Ready;
}

void MystingsTurn::MoveChar()
{
    auto Char = GetCurrentChar();
    AMystingsPlayerController* player = Cast<AMystingsPlayerController>(Char->GetController());
    
    if(IsPlayerTurn() && player) {
        auto TileManager = player->GetCurrentTile()->GetManager();
        if(TileManager && Movement == Pressed && IsValidMove()) {
            TileManager->BFS(player->GetCurrentTile(), 4, ATileManager::Show(), false);
            Movement = Doing;
        }
        // Once the Character has reached his destination tile
        if(TileManager && Char->GetReached() && Movement == Doing) {
            TileManager->BFS(Char->GetOriginTile(), 4, ATileManager::Hide(), true);
            Char->SetReached(false);
            NextMove();
            ResetButtons();
        }
    }
}

void MystingsTurn::HealChar()
{
    auto Char = GetCurrentChar();
    AMystingsPlayerController* player = Cast<AMystingsPlayerController>(Char->GetController());
    
    if(IsPlayerTurn() && player && IsValidMove() && Heal == Pressed) {
        Char->MystingsHeal(10.f);
        NextMove();
        ResetButtons();
    }
}

void MystingsTurn::ExecuteAI()
{
    auto Char = GetCurrentChar();
    
    AEnemyAIController* AIC = Cast<AEnemyAIController>(Char->GetController());
    if(AIC && NPC == Ready) {
        AIC->ExecuteMove();
        NPC = Doing;
    }
    // Wait for the NPC to execute his move
    if(AIC && NPC == Doing) {
        // Once the NPC has reached his destination tile or has attacked the player
        if((Char->GetReached() && !Char->IsMoving()) || Char->HasAttacked()) {
            Char->SetReached(false);
            Char->SetHasAttacked(false);
            NextMove();
            NPC = Ready;
        }
    }
}

bool MystingsTurn::WithinShootingRange(AMystingsCharacter* Enemy, int32 range)
{
    auto Player = GetPlayerChar();
    FVector2D diff = Player->GetCurrentTile()->GetGridPos() - Enemy->GetCurrentTile()->GetGridPos();
    int32 ManDis = FMath::Abs(diff.X) + FMath::Abs(diff.Y);
    
    return ManDis <= range;
}

void MystingsTurn::AttackChar()
{
    auto Char = GetCurrentChar();
    AMystingsPlayerController* player = Cast<AMystingsPlayerController>(Char->GetController());
    
    if(IsPlayerTurn() && player) {
        // Once the player has pressed the attack button
        if(Attack == Pressed && IsValidMove()) {
            // This flag is true if there is an avalable NPC to attack
            bool bTargetAvailable = false;
            
            for(auto Enemy : Chars) {
                if(Enemy->IsPlayer()) continue;
                if(GetPlayerChar()->InRange(Enemy,6) && GetPlayerChar()->WeaponTrace(Enemy)) {
                    Enemy->GetCurrentTile()->SetActorHiddenInGame(false);
                    bTargetAvailable = true;
                }
            }
            
            if(bTargetAvailable) {
                Attack = Doing;
                player->SetIsAttacking(true);
            }
        }
        // Once the player has attacked an enemy
        if(Char->HasAttacked() && Attack == Doing) {
            for(auto Enemy : Chars) {
                if(Enemy->IsPlayer()) continue;
                // Unhighlight and hide the tiles under the NPCs
                Enemy->GetCurrentTile()->Highlight(false, true);
                Enemy->GetCurrentTile()->SetActorHiddenInGame(true);
            }
            
            ResetButtons();
            player->SetIsAttacking(false);
            Char->SetHasAttacked(false);
            NextMove();
        }
    }
}

bool MystingsTurn::PlayerHasWon()
{
    if(Chars.Num() == 1) {
        if(Chars[0]->IsPlayer()) return true;
    }
    return false;
}

int32 MystingsTurn::NextTurn()
{
    if(MoveID == 0) {
        if(++TurnID >= Chars.Num()) TurnID = 0;
    }
    return TurnID;
}

int32 MystingsTurn::NextMove()
{
    if(++MoveID >= NumMoves) {
        MoveID = 0;
        NextTurn();
    }
    return MoveID;
}
