// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "colorepoGameMode.generated.h"

UCLASS(minimalapi)
class AcolorepoGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	AcolorepoGameMode();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool WhichPlayerWins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CurrentLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumberOfAI;
	virtual void BeginPlay() override;
};



