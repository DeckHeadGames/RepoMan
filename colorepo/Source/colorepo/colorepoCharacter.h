// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "colorepoCharacter.generated.h"



UCLASS(config=Game)
class AcolorepoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AcolorepoCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	int CurrentColor;
	int ColorOnDeck;
	bool GetIsWithin();
	void SetIsWithin(bool value);
	bool DoDestroy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundCue* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundCue* BurstSound;
	



protected:
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* BoundingBox;
	bool IsWithin;
	const int Red = 1;
	const int Orange = 2;
	const int Yellow = 3;
	const int Green = 4;
	const int Blue = 5;
	const int Indigo = 6;
	const int Violet = 7;

	UAudioComponent* PlaySound(class USoundCue *Sound);

	void SetCurrentColor(float number);
	float GetCurrentColor();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void FireLightWave();
	void FireLightBurstDown();
	void FireLightBurstUp();
	void FireManager();
	void CannotFire();
	void CannotBurst();

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ALightWave> RedProjectile;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ALightWave> OrangeProjectile;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ALightWave> YellowProjectile;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ALightWave> GreenProjectile;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ALightWave> BlueProjectile;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ALightWave> IndigoProjectile;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ALightWave> VioletProjectile;

	bool CanFire;
	bool BurstBool;
	FTimerHandle Cooldown;
	float SpeedModifier;
	void xPressed();
	void xReleased();
	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

