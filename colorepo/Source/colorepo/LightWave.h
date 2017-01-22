// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LightWave.generated.h"

UCLASS()
class COLOREPO_API ALightWave : public AActor
{
	GENERATED_BODY()
		UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;

public:
	// Sets default values for this actor's properties
	ALightWave();

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	void SetInitialForward(FVector direction);
	FVector GetInitialForward();
	
	void SetColor(int index);
	void SetSecondary(bool value);

protected:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector InitialForward;
	void SetFrequency(float number);
	const float Violet = 90.0f;
	const float Indigo = 78.0f;
	const float Blue = 66.0f;
	const float Green = 54.0f;
	const float Yellow = 42.0f;
	const float Orange = 30.0f;
	const float Red = 18.0f;
	bool SecondaryFire;
	int MyColor;
	float xValue;
	float frequency;
};
