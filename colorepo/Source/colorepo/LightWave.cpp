// Fill out your copyright notice in the Description page of Project Settings.

#include "colorepo.h"
#include "LightWave.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"
#include "colorepoCharacter.h"
#include <cmath>


// Sets default values
ALightWave::ALightWave()
{
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere for colisions at the tip of our wave
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ALightWave::OnHit);	
	SecondaryFire = false;
	
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 0.0f;
	ProjectileMovement->MaxSpeed = 10000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialForward = ProjectileMovement->Velocity;
	xValue = 0.0f;
	frequency = 10.0f;
	MyColor = 0;

}

void ALightWave::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALightWave::Tick( float DeltaTime )
{
	//Calculate the 'waviness' of our wave using sin
	Super::Tick( DeltaTime );
	xValue += DeltaTime;
	FMath::Clamp(frequency, 10.0f, 100.0f);
	if (SecondaryFire) {
		if ((10.0f - xValue) < 0) {
			this->Destroy();
		}
		else {
			InitialForward *= 1.125;
			ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f, (30.0f * (5.0f - xValue)), 0));
		}
	}
	else {
		FVector temp = InitialForward;
		temp.Normalize();
		FVector forcross = FVector(0, 0, 1);
		FVector ResultVector = FVector::CrossProduct(temp, forcross);
		ResultVector.Normalize();
		ProjectileMovement->Velocity = InitialForward + ((2500.0f * sin(xValue*frequency))* ResultVector);
	}
	

}

void ALightWave::SetSecondary(bool value) {
	SecondaryFire = value;
	InitialForward = InitialForward / 1000.0f;
}

void ALightWave::SetInitialForward(FVector direction) {
	InitialForward = direction;
}

FVector ALightWave::GetInitialForward() {
	return InitialForward;
}

void ALightWave::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (!OtherActor->IsA(AcolorepoCharacter::StaticClass())) {
		//If we hit anything, destroy the wave
		this->Destroy();
	}
	if (OtherActor->IsA(AcolorepoCharacter::StaticClass())) {
		//If we hit a player, add an impulse to them
		AcolorepoCharacter*  temp = Cast<AcolorepoCharacter>(OtherActor);
		FVector Impulse = InitialForward;
		Impulse.Normalize();
		temp->LaunchCharacter(Impulse * 4000.0f * MyColor, true, true);
		this->Destroy();
	}
	
}

void ALightWave::SetFrequency(float number) {
	frequency = number;
}

void ALightWave::SetColor(int index) {
	//Change wave frequency/wavelength based on color
	switch (index) {
	case 1:
		SetFrequency(Red);
		MyColor = 8 - index;
		break;
	case 2:
		SetFrequency(Orange);
		MyColor = 8 - index;
		break;
	case 3:
		SetFrequency(Yellow);
		MyColor = 8 - index;
		break;
	case 4:
		SetFrequency(Green);
		MyColor = 8 - index;
		break;
	case 5:
		SetFrequency(Blue);
		MyColor = 8 - index;
		break;
	case 6:
		SetFrequency(Indigo);
		MyColor = 8 - index;
		break;
	case 7:
		SetFrequency(Violet);
		MyColor = 8 - index;
		break;
	default:
		break;
	}
}
