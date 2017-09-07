// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <iostream>
#include "MystingsCharacter.h"
/**
 * 
 */
class MYSTINGS_API MystingsTurn
{
public:
    enum State { Ready, Pressed, Doing };
    
	MystingsTurn();
	~MystingsTurn();
    
    void AddPlayer(AMystingsCharacter* Char);
    int32 NextTurn();
    
    int32 NextMove();
    
    AMystingsCharacter* GetPlayerChar() { return Chars[0]; }
    AMystingsCharacter* GetCurrentChar() { return Chars[TurnID]; }
    int32 GetTurnID() { return TurnID; }
    
    bool IsPlayerTurn() { return TurnID == 0; }
    bool PlayerHasWon();
    
    bool IsValidMove();
    
    bool WithinShootingRange(AMystingsCharacter* Enemy, int32 range);
    
    void ResetButtons();
    UFUNCTION(BlueprintCallable,Category="MystingsTurn")
    void MoveChar();
    UFUNCTION(BlueprintCallable,Category="MystingsTurn")
    void AttackChar();
    UFUNCTION(BlueprintCallable,Category="MystingsTurn")
    void HealChar();
    
    void ExecuteAI();
    
    State Movement = Ready;
    State Attack = Ready;
    State Heal = Ready;
    
    State NPC = Ready;
private:
    TArray<AMystingsCharacter*> Chars;
    int32 TurnID = 0;
    
    int32 NumMoves = 2;
    int32 MoveID = 0;
};
