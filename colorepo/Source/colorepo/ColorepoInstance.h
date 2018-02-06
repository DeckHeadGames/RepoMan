// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "ColorepoInstance.generated.h"

/**
 * 
 */
UCLASS()
class COLOREPO_API UColorepoInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CurrentLevel = FString("Main");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumberOfEnemies;
	
	
	
};
