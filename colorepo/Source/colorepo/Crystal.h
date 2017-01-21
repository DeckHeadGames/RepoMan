// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Crystal.generated.h"

UCLASS()
class COLOREPO_API ACrystal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrystal();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CrystalColor;

private:
	//UPROPERTY(VisibleDefaultsOnly)
	//	class USphereComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* BoundingBox;

	
};
