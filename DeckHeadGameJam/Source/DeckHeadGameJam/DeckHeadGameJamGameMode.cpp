// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DeckHeadGameJam.h"
#include "DeckHeadGameJamGameMode.h"
#include "DeckHeadGameJamCharacter.h"

ADeckHeadGameJamGameMode::ADeckHeadGameJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
