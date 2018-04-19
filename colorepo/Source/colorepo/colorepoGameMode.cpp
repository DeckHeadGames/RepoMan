// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "colorepo.h"
#include "colorepoGameMode.h"
#include "colorepoCharacter.h"
#include "ColorepoCharacterController.h"

AcolorepoGameMode::AcolorepoGameMode()
{

	PlayerControllerClass = AColorepoCharacterController::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/colorepoCharacter_BP"));
	CurrentLevel = FName("Main");
	NumberOfAI = 1;
	WhichPlayerWins = true;
}

void AcolorepoGameMode::BeginPlay() {
	
	UGameplayStatics::CreatePlayer(GetWorld(), 0, true);
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
}

