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

	// set our turn rates for input
	BaseTurnRate = 180.0f;
	BaseLookUpRate = 180.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


	CanFire = true;
	BurstBool = false;
	IsWithin = false;
	SpeedModifier = 1.0f;
	DoDestroy = false;
	Delay = 1.5f;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AcolorepoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
}

void AcolorepoCharacter::SecondaryFireManager() {
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

//void AcolorepoCharacter::FireCircle() {
//	// try and fire a projectile
//	TSubclassOf<ALightWave> ProjectileClass;
//	switch (ColorOnDeck) {
//	case 1:
//		ProjectileClass = RedProjectile;
//		break;
//	case 2:
//		ProjectileClass = OrangeProjectile;
//		break;
//	case 3:
//		ProjectileClass = YellowProjectile;
//		break;
//	case 4:
//		ProjectileClass = GreenProjectile;
//		break;
//	case 5:
//		ProjectileClass = BlueProjectile;
//		break;
//	case 6:
//		ProjectileClass = IndigoProjectile;
//		break;
//	case 7:
//		ProjectileClass = VioletProjectile;
//		break;
//	default:
//		break;
//	}
//	if (ProjectileClass != NULL)
//	{
//		UWorld* const World = GetWorld();
//		if (World != NULL)
//		{
//			//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Cyan, TEXT("I shot a wave"), true);
//			FVector CurrentLocation = this->GetActorLocation();
//			FVector OurForwards = this->GetActorForwardVector();
//			FVector OurUp = this->GetActorUpVector();
//			OurUp.Normalize();
//			OurForwards.Normalize();
//			FVector DeltaForwards = OurForwards*150.0f;
//			FVector DeltaUp = OurUp*20.0f;
//			ALightWave* ShotWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp, this->GetActorRotation());
//			float magnitudeSquared = FVector::DotProduct(this->GetActorForwardVector(), this->GetActorForwardVector());
//			float magnitude = sqrt(magnitudeSquared);
//			ShotWave->ProjectileMovement->SetVelocityInLocalSpace(FVector((1000.0f + magnitude)* SpeedModifier, 0.0f, 0.0f));
//			ShotWave->SetInitialForward(ShotWave->ProjectileMovement->Velocity);
//			ShotWave->SetColor(ColorOnDeck);
//			ShotWave->SetSecondary(true);
//			UAudioComponent* temp = PlaySound(BurstSound);
//
//		}
//	}
//
//}

void AcolorepoCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}


void AcolorepoCharacter::xPressed() {
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, FString("E button pressed"));
	DoDestroy = true;
}

void AcolorepoCharacter::xReleased() {
	DoDestroy = false;
	UAudioComponent* temp = PlaySound(PickupSound);
}

void AcolorepoCharacter::FireManager(float moretime) {
	CanFire = false;
	int Value = 8 - ColorOnDeck;
	GetWorldTimerManager().SetTimer(Cooldown, this, &AcolorepoCharacter::CannotFire,
		(0.2f * Value) + moretime, false);
}

void AcolorepoCharacter::CannotFire() {
	CanFire = true;
}

void AcolorepoCharacter::FireLightBurstDown() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Cyan, TEXT("BurstDown"), true);
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
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Cyan, TEXT("BurstUp"), true);
	if (BurstBool) {
		// try and fire a projectile
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
				FVector DeltaRight = Right * 100;
				FVector MoreRight = Right * 200;
				FVector DeltaLeft = Right * -100;
				FVector MoreLeft = Right * -200;
				ALightWave* RWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp + DeltaRight, this->GetActorRotation());
				ALightWave* SWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp + DeltaLeft, this->GetActorRotation());
				ALightWave* RRWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp + MoreRight, this->GetActorRotation());
				ALightWave* SSWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp + MoreLeft, this->GetActorRotation());
				RWave->ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f + magnitude, 300.0f, 0.0f));
				SWave->ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f + magnitude, -300.0f, 0.0f));
				RRWave->ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f + magnitude, 600.0f, 0.0f));
				SSWave->ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f + magnitude, -600.0f, 0.0f));
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
	BurstBool = true;
}

void AcolorepoCharacter::FireLightWave() {
	// try and fire a projectilerstBool = false;
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

FVector AcolorepoCharacter::GetMoveDirection(float DeltaSeconds) {
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);
	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
	// Calculate  movement
	return (MoveDirection * MoveSpeed * DeltaSeconds);
}

FVector AcolorepoCharacter::GetFireDirection() {
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);
	return FireDirection;
}

void AcolorepoCharacter::MoveColorepoCharacter(FVector Movement, FVector FireDirection) {
	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		//const FRotator NewRotation = Movement.Rotation();
		if (FireDirection.SizeSquared() > 0.0f) {
			FHitResult Hit(1.f);

			RootComponent->MoveComponent(Movement, FireDirection.Rotation(), true, &Hit);

			if (Hit.IsValidBlockingHit())
			{
				const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
				const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
				RootComponent->MoveComponent(Deflection, FireDirection.Rotation(), true);
			}
		}
		else {
			FHitResult Hit(1.f);

			RootComponent->MoveComponent(Movement, this->GetActorRotation(), true, &Hit);

			if (Hit.IsValidBlockingHit())
			{
				const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
				const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
				RootComponent->MoveComponent(Deflection, this->GetActorRotation(), true);
			}
		}
	}
	else if (FireDirection.SizeSquared() > 0.0f) {
		this->SetActorRotation(FireDirection.Rotation());
	}
}

void AcolorepoCharacter::UpdateFireDirection(FVector FireDirection, float DeltaSeconds) {
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


