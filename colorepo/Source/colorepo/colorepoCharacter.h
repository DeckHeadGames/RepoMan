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

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	int CurrentColor;
	bool GetIsWithin();
	void SetIsWithin(bool value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundCue* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundCue* BurstSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundCue* PickupSound;

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int ColorOnDeck;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool DoDestroy;

	UFUNCTION(BlueprintCallable, Category = "Laser")
		void SecondaryFireManager();

	UFUNCTION(BlueprintCallable, Category = "Laser")
		void FireLightWave();

	UFUNCTION(BlueprintCallable, Category = "Laser")
		void RedSecondary();

	UFUNCTION(BlueprintCallable, Category = "Laser")
		void OrangeSecondary();

	UFUNCTION(BlueprintCallable, Category = "Laser")
		void YellowSecondary();

	UFUNCTION(BlueprintCallable, Category = "Laser")
		void GreenSecondary();

	UFUNCTION(BlueprintCallable, Category = "Laser")
		void BlueSecondary();

	UFUNCTION(BlueprintCallable, Category = "Laser")
		void IndigoSecondary();

	UFUNCTION(BlueprintCallable, Category = "Laser")
		void VioletSecondary();

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void UpdateFireDirection(FVector FireDirection, float DeltaSeconds);

	void FireLightBurstDown();
	void FireLightBurstUp();
	void xPressed();
	void xReleased();


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


	/** Resets HMD orientation in VR. */
	void OnResetVR();

	void FireManager(float moretime);
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
	float Delay;
	

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

