// Fill out your copyright notice in the Description page of Project Settings.

#include "colorepo.h"
#include "Engine.h"
#include "colorepoGameMode.h"
#include "ColorepoInstance.h"
#include "ColorepoCharacterController.h"
#include "colorepoCharacter.h"

const FName AColorepoCharacterController::MoveForwardBinding("MoveForward");
const FName AColorepoCharacterController::MoveRightBinding("MoveRight");
const FName AColorepoCharacterController::FireForwardBinding("LookUp");
const FName AColorepoCharacterController::FireRightBinding("Turn");

AColorepoCharacterController::AColorepoCharacterController() {
	bShowMouseCursor = true;
	//Allow mouse input
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	FireVector = FVector(0.0f, 0.0f, 0.0f);
}

void AColorepoCharacterController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);
	if (CanPlay()) {
		//Move character and update rotation
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		const FVector Movement = GetMoveDirection(DeltaTime);
		const FVector FireDirection = GetFireDirection();
		MoveColorepoCharacter(Movement, FireDirection, DeltaTime);
		MyColorepoCharacter->UpdateFireDirection(FireDirection, DeltaTime);
	}
}

void AColorepoCharacterController::SetupInputComponent( ) {
	//Set up Input Bindings
	Super::SetupInputComponent();
		InputComponent->BindAxis(MoveForwardBinding);
		InputComponent->BindAxis(MoveRightBinding);
		InputComponent->BindAxis(FireForwardBinding);
		InputComponent->BindAxis(FireRightBinding);

		InputComponent->BindAction("FireLightBurst", IE_Pressed, this, &AColorepoCharacterController::FireLightBurstDown);
		InputComponent->BindAction("FireLightBurst", IE_Released, this, &AColorepoCharacterController::FireLightBurstUp);
		InputComponent->BindAction("RemoveCrystal", IE_Pressed, this, &AColorepoCharacterController::xPressed);
		InputComponent->BindAction("RemoveCrystal", IE_Released, this, &AColorepoCharacterController::xReleased);
		InputComponent->BindAction("FireCircle", IE_Pressed, this, &AColorepoCharacterController::FireSecondary);

}

FVector AColorepoCharacterController::GetMoveDirection(float DeltaSeconds) {
	//Get axis values
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);
	FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
	MoveDirection.Normalize();
	return (MoveDirection);
}

FVector AColorepoCharacterController::GetFireDirection() {
	//Find direction character should face, different for using keyboard and mouse controls vs gamepad
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	UColorepoInstance* ginstance = Cast<UColorepoInstance>(GetGameInstance());
	if (ginstance->KeyboardMouse) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			FireVector = Hit.ImpactPoint - MyColorepoCharacter->GetActorLocation();
			FireVector.Z = 0.0f;
		}
	}
	else {
		if (FireForwardValue != 0.0f && FireRightValue != 0.0f) {
			FireVector = FVector(FireForwardValue, FireRightValue, 0.f);
		}
	}
	return FireVector;
}

void AColorepoCharacterController::MoveColorepoCharacter(FVector Movement, FVector FireDirection, float DeltaTime) {
	//Move the character
	AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
	MyColorepoCharacter->AddMovementInput(Movement, 1000.0f * DeltaTime);
	FRotator direction = FireDirection.Rotation();
	MyColorepoCharacter->SetActorRotation(direction);
}

void AColorepoCharacterController::FireLightBurstDown() {
	if (CanPlay()) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		MyColorepoCharacter->FireLightBurstDown();
	}

}

void AColorepoCharacterController::FireLightBurstUp() {
	if (CanPlay()) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		MyColorepoCharacter->FireLightBurstUp();
	}
}

void AColorepoCharacterController::xPressed() {
	if (CanPlay()) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		MyColorepoCharacter->xPressed();
	}

}

void AColorepoCharacterController::xReleased() {
	if (CanPlay()) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		MyColorepoCharacter->xReleased();
	}

}


void AColorepoCharacterController::FireSecondary() {
	if (CanPlay()) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		MyColorepoCharacter->SecondaryFireManager();
	}

}

bool AColorepoCharacterController::CanPlay() {
	//Make sure that we don't get a null reference on our character based on what level we are in
	UColorepoInstance* ginstance = Cast<UColorepoInstance>(GetGameInstance());
	FString Levelname = ginstance->CurrentLevel;
	if (Levelname != FString("Main") && Levelname != FString("End") && Levelname != FString("Pause")) {
		return true;
	}
	else {
		return false;
	}
}
