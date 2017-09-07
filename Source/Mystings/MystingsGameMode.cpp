// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Mystings.h"
#include "MystingsGameMode.h"

#include "MystingsPlayerController.h"
#include "MystingsCharacter.h"
#include "TileManager.h"

AMystingsGameMode::AMystingsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMystingsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMystingsGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    auto controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
    AMystingsPlayerController* player = Cast<AMystingsPlayerController>(controller);
    
    auto Char = Turn.GetCurrentChar();
    // Change camera position to face turn's character
    if(player) player->SetViewTargetWithBlend(Char);
    
    if(Turn.IsPlayerTurn()) {
        // Either of these are executed depending on which button is pressed
        Turn.MoveChar();
        Turn.AttackChar();
        Turn.HealChar();
    } else {
        Turn.ExecuteAI();
    }
}

void AMystingsGameMode::MoveChar()
{
    Turn.Movement = MystingsTurn::Pressed;
}

void AMystingsGameMode::AttackChar()
{
    Turn.Attack = MystingsTurn::Pressed;
}

void AMystingsGameMode::HealChar()
{
    Turn.Heal = MystingsTurn::Pressed;
}

bool AMystingsGameMode::PlayerHasWon()
{
    return Turn.PlayerHasWon();
}
