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
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ALightWave::OnHit);		// set up a notification for when this component hits something blocking

																					// Players can't walk on it
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

}

// Called when the game starts or when spawned
void ALightWave::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightWave::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	xValue += DeltaTime;
	ProjectileMovement->Velocity = InitialForward + FVector(0.0f, 1000.0f * sin(xValue*frequency), 0.0f);

}

void ALightWave::SetInitialForward(FVector direction) {
	InitialForward = direction;
}

FVector ALightWave::GetInitialForward() {
	return InitialForward;
}

void ALightWave::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (!OtherActor->IsA(AcolorepoCharacter::StaticClass())) {
		this->Destroy();
	}
	
}

void ALightWave::SetFrequency(float number) {
	frequency = number;
}

float ALightWave::GetFrequency() {
	return frequency;
}
