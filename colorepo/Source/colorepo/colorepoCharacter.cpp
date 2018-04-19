// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "colorepo.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "colorepoCharacter.h"
#include "LightWave.h"
#include "Engine.h"
#include "Crystal.h"
#include <cmath>

//////////////////////////////////////////////////////////////////////////
// AcolorepoCharacter

const FName AcolorepoCharacter::MoveForwardBinding("MoveForward");
const FName AcolorepoCharacter::MoveRightBinding("MoveRight");
const FName AcolorepoCharacter::FireForwardBinding("LookUp");
const FName AcolorepoCharacter::FireRightBinding("Turn");

AcolorepoCharacter::AcolorepoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


	CanFire = true;
	BurstBool = false;
	IsWithin = false;
	SpeedModifier = 1.0f;
	DoDestroy = false;
	Delay = 1.5f;
}


void AcolorepoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
}

void AcolorepoCharacter::SecondaryFireManager() {
	//The manager calls a different secondary fire function based on what color the player has picked up
	switch (CurrentColor) {
	case 1:
		RedSecondary();
		break;
	case 2:
		OrangeSecondary();
		break;
	case 3:
		YellowSecondary();
		break;
	case 4:
		GreenSecondary();
		break;
	case 5:
		BlueSecondary();
		break;
	case 6:
		IndigoSecondary();
		break;
	case 7:
		VioletSecondary();
		break;
	default:
		break;
	}
}

//These functions don't do anything right now
//TODO: Make secondary fire functions
void AcolorepoCharacter::RedSecondary() {
	TSubclassOf<ALightWave> ProjectileClass;
	ProjectileClass = RedProjectile;
}
void AcolorepoCharacter::OrangeSecondary() {
	TSubclassOf<ALightWave> ProjectileClass;
	ProjectileClass = OrangeProjectile;
}
void AcolorepoCharacter::YellowSecondary() {
	TSubclassOf<ALightWave> ProjectileClass;
	ProjectileClass = YellowProjectile;
}
void AcolorepoCharacter::GreenSecondary() {
	TSubclassOf<ALightWave> ProjectileClass;
	ProjectileClass = GreenProjectile;
}
void AcolorepoCharacter::BlueSecondary() {
	TSubclassOf<ALightWave> ProjectileClass;
	ProjectileClass = BlueProjectile;
}
void AcolorepoCharacter::IndigoSecondary() {
	TSubclassOf<ALightWave> ProjectileClass;
	ProjectileClass = IndigoProjectile;
}
void AcolorepoCharacter::VioletSecondary() {
	TSubclassOf<ALightWave> ProjectileClass;
	ProjectileClass = VioletProjectile;
}



void AcolorepoCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}


void AcolorepoCharacter::xPressed() {
	DoDestroy = true;
}

void AcolorepoCharacter::xReleased() {
	DoDestroy = false;
	UAudioComponent* temp = PlaySound(PickupSound);
}

void AcolorepoCharacter::FireManager(float moretime) {
	//Manages cooldown on firing
	CanFire = false;
	int Value = 8 - ColorOnDeck;
	GetWorldTimerManager().SetTimer(Cooldown, this, &AcolorepoCharacter::CannotFire,
		(0.2f * Value) + moretime, false);
}

void AcolorepoCharacter::CannotFire() {
	//Allows for firing after cooldown 
	CanFire = true;
}

void AcolorepoCharacter::FireLightBurstDown() {
	//Must charge up light wave burst
	GetWorldTimerManager().SetTimer(Cooldown, this, &AcolorepoCharacter::CannotBurst,
		Delay, false);
}

UAudioComponent* AcolorepoCharacter::PlaySound(class USoundCue* Sound) {
	UAudioComponent* AC = NULL;
	if (Sound)
	{
		AC = UGameplayStatics::SpawnSoundAttached(Sound, this->GetMesh());
	}
	return AC;
}

void AcolorepoCharacter::FireLightBurstUp() {
	//Fire 4 projectiles 
	if (BurstBool) {
		TSubclassOf<ALightWave> ProjectileClass;
		switch (ColorOnDeck) {
		case 1:
			ProjectileClass = RedProjectile;
			break;
		case 2:
			ProjectileClass = OrangeProjectile;
			break;
		case 3:
			ProjectileClass = YellowProjectile;
			break;
		case 4:
			ProjectileClass = GreenProjectile;
			break;
		case 5:
			ProjectileClass = BlueProjectile;
			break;
		case 6:
			ProjectileClass = IndigoProjectile;
			break;
		case 7:
			ProjectileClass = VioletProjectile;
			break;
		default:
			break;
		}
		if (ProjectileClass != NULL )
		{
			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				FVector CurrentLocation = this->GetActorLocation();
				FVector OurForwards = this->GetActorForwardVector();
				FVector OurUp = this->GetActorUpVector();
				OurUp.Normalize();
				OurForwards.Normalize();
				FVector DeltaForwards = OurForwards*100.0f;
				FVector DeltaUp = OurUp*20.0f;
				ALightWave* ShotWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp, this->GetActorRotation());
				float magnitudeSquared = FVector::DotProduct(this->GetActorForwardVector(), this->GetActorForwardVector());
				float magnitude = sqrt(magnitudeSquared);
				ShotWave->ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f + magnitude, 0.0f, 0.0f));
				ShotWave->SetInitialForward(ShotWave->ProjectileMovement->Velocity);
				ShotWave->SetColor(ColorOnDeck);
				FVector Right = this->GetActorRightVector();

				//Spawn projectile actors
				ALightWave* RWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp + (Right * 100), this->GetActorRotation());
				ALightWave* SWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp + (Right * -100), this->GetActorRotation());
				ALightWave* RRWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp + (Right * 200), this->GetActorRotation());
				ALightWave* SSWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp + (Right * -200), this->GetActorRotation());
				
				//set their velocity
				RWave->ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f + magnitude, 300.0f, 0.0f));
				SWave->ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f + magnitude, -300.0f, 0.0f));
				RRWave->ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f + magnitude, 600.0f, 0.0f));
				SSWave->ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f + magnitude, -600.0f, 0.0f));
				
				//Set initial vector and color of the projectiles
				RWave->SetInitialForward(RWave->ProjectileMovement->Velocity);
				SWave->SetInitialForward(SWave->ProjectileMovement->Velocity);
				RWave->SetColor(ColorOnDeck);
				SWave->SetColor(ColorOnDeck);
				RRWave->SetInitialForward(RRWave->ProjectileMovement->Velocity);
				SSWave->SetInitialForward(SSWave->ProjectileMovement->Velocity);
				RRWave->SetColor(ColorOnDeck);
				SSWave->SetColor(ColorOnDeck);

				ShotWave->SetSecondary(true);
				auto temp = PlaySound(BurstSound);
				BurstBool = false;
				CanFire = true;
			}
		}
	}
}

void AcolorepoCharacter::CannotBurst() {
	//Restrict player from firing light burst
	BurstBool = true;
}

void AcolorepoCharacter::FireLightWave() {
	//Fire a light wave in the direction the character is facing. 
	TSubclassOf<ALightWave> ProjectileClass;
	switch (ColorOnDeck) {
	case 1:
		ProjectileClass = RedProjectile;
		break;
	case 2:
		ProjectileClass = OrangeProjectile;
		break;
	case 3:
		ProjectileClass = YellowProjectile;
		break;
	case 4:
		ProjectileClass = GreenProjectile;
		break;
	case 5:
		ProjectileClass = BlueProjectile;
		break;
	case 6:
		ProjectileClass = IndigoProjectile;
		break;
	case 7:
		ProjectileClass = VioletProjectile;
		break;
	default:
		break;
	}
	if (ProjectileClass != NULL && CanFire)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
				FVector CurrentLocation = this->GetActorLocation();
				FVector OurForwards = this->GetActorForwardVector();
				FVector OurUp = this->GetActorUpVector();
				OurUp.Normalize();
				OurForwards.Normalize();
				FVector OurVel = this->GetVelocity();
				OurVel.Normalize();
				FVector DeltaForwards = (OurForwards*100.0f) + (FVector::DotProduct(OurVel, OurForwards) * OurForwards * 30.0f);
				FVector DeltaUp = OurUp*20.0f;
				ALightWave* ShotWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp, this->GetActorRotation());
				ShotWave->ProjectileMovement->SetVelocityInLocalSpace(FVector((1000.0f), 0.0f, 0.0f));
				ShotWave->SetInitialForward(ShotWave->ProjectileMovement->Velocity);
				ShotWave->SetColor(ColorOnDeck);
				UAudioComponent* temp = PlaySound(FireSound);
				FireManager(0.0f);
		}
	}
}

bool AcolorepoCharacter::GetIsWithin() {
	return IsWithin;
}

void AcolorepoCharacter::SetIsWithin(bool value) {
	IsWithin = value;
}

void AcolorepoCharacter::UpdateFireDirection(FVector FireDirection, float DeltaSeconds) {
	//Always fire a shot if we are aiming in a certain direction
	CurrentColor = ColorOnDeck;
	if (SpeedModifier <= 5.0f) {
		SpeedModifier += (DeltaSeconds / 20);
	}

	if (FireDirection != FVector(0.0f, 0.0f, 0.0f)) {
		FireLightWave();
	}
}

void AcolorepoCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}


