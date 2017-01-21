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

AcolorepoCharacter::AcolorepoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 15.f;
	BaseLookUpRate = 15.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	BoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	CurrentColor = Green;
	CanFire = true;
	IsWithin = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AcolorepoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AcolorepoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AcolorepoCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AcolorepoCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AcolorepoCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AcolorepoCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AcolorepoCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AcolorepoCharacter::OnResetVR);
	PlayerInputComponent->BindAction("FireLightWave", IE_Pressed, this, &AcolorepoCharacter::FireLightWave);
}

void AcolorepoCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AcolorepoCharacter::SetCurrentColor(float number) {
	CurrentColor = number;
}

float AcolorepoCharacter::GetCurrentColor() {
	return CurrentColor;
}

void AcolorepoCharacter::FireManager() {
	CanFire = false;
	int Value = 8 - CurrentColor;
	GetWorldTimerManager().SetTimer(Cooldown, this, &AcolorepoCharacter::CannotFire,
		0.2f * Value, false);
}

void AcolorepoCharacter::CannotFire() {
	CanFire = true;
}

void AcolorepoCharacter::FireLightWave() {
	// try and fire a projectile
	TSubclassOf<ALightWave> ProjectileClass;
	switch (CurrentColor) {
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
				GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Cyan, TEXT("I shot a wave"), true);
				FVector CurrentLocation = this->GetActorLocation();
				FVector OurForwards = this->GetActorForwardVector();
				FVector OurUp = this->GetActorUpVector();
				OurUp.Normalize();
				OurForwards.Normalize();
				FVector DeltaForwards = OurForwards*60.0f;
				FVector DeltaUp = OurUp*20.0f;
				ALightWave* ShotWave = World->SpawnActor<ALightWave>(ProjectileClass, CurrentLocation + DeltaForwards + DeltaUp, this->GetActorRotation());
				float magnitudeSquared = FVector::DotProduct(this->GetActorForwardVector(), this->GetActorForwardVector());
				float magnitude = sqrt(magnitudeSquared);
				ShotWave->ProjectileMovement->SetVelocityInLocalSpace(FVector(1000.0f + magnitude, 0.0f, 0.0f));
				ShotWave->SetInitialForward(ShotWave->ProjectileMovement->Velocity);
				ShotWave->SetColor(CurrentColor);
				if (CurrentColor == Violet) {
					//CurrentColor = Red;
				}
				else {
					//CurrentColor++;
				}
				FireManager();
		}
	}
}

bool AcolorepoCharacter::GetIsWithin() {
	return IsWithin;
}

void AcolorepoCharacter::SetIsWithin(bool value) {
	IsWithin = value;
}

void AcolorepoCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	CurrentColor = ColorOnDeck;
}

void AcolorepoCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AcolorepoCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AcolorepoCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AcolorepoCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AcolorepoCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AcolorepoCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
