// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ColorepoCharacterController.generated.h"


/**
 * 
 */
UCLASS()
class COLOREPO_API AColorepoCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	AColorepoCharacterController();
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;
	UPROPERTY(BlueprintReadWrite)
		FVector FireVector;

protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		FVector GetMoveDirection(float DeltaSeconds);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		FVector GetFireDirection();
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveColorepoCharacter(FVector Movement, FVector FireDirection, float DeltaTime);
	void FireLightBurstDown();
	void FireLightBurstUp();
	bool CanPlay();
	void xPressed();
	void xReleased();
	void FireSecondary();

	
};
