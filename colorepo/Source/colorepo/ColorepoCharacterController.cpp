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
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AColorepoCharacterController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);
	UColorepoInstance* ginstance = Cast<UColorepoInstance>(GetGameInstance());
	Levelname = ginstance->CurrentLevel;
	if (Levelname != FString("Main") && Levelname != FString("End")) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		const FVector Movement = GetMoveDirection(DeltaTime);
		const FVector FireDirection = GetFireDirection();
		MoveColorepoCharacter(Movement, FireDirection, DeltaTime);
		MyColorepoCharacter->UpdateFireDirection(FireDirection, DeltaTime);
	}
}

void AColorepoCharacterController::SetupInputComponent( ) {
	Super::SetupInputComponent();
		InputComponent->BindAxis(MoveForwardBinding);
		InputComponent->BindAxis(MoveRightBinding);
		InputComponent->BindAxis(FireForwardBinding);
		InputComponent->BindAxis(FireRightBinding);

		//PlayerInputComponent->BindAction("FireLightWave", IE_Pressed, this, &AcolorepoCharacter::FireLightWave);
		InputComponent->BindAction("FireLightBurst", IE_Pressed, this, &AColorepoCharacterController::FireLightBurstDown);
		InputComponent->BindAction("FireLightBurst", IE_Released, this, &AColorepoCharacterController::FireLightBurstUp);
		InputComponent->BindAction("RemoveCrystal", IE_Pressed, this, &AColorepoCharacterController::xPressed);
		InputComponent->BindAction("RemoveCrystal", IE_Released, this, &AColorepoCharacterController::xReleased);
		InputComponent->BindAction("FireCircle", IE_Pressed, this, &AColorepoCharacterController::FireCircle);

}

FVector AColorepoCharacterController::GetMoveDirection(float DeltaSeconds) {
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);
	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
	// Calculate  movement
	MoveDirection.Normalize();
	return (MoveDirection);
}

FVector AColorepoCharacterController::GetFireDirection() {
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	FVector FireDirection = FVector(0.0f, 0.0f, 0.0f);
	if (FireForwardValue != 0.0f && FireRightValue != 0.0f) {
		FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);
	}
	else {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			FireDirection = Hit.ImpactPoint - MyColorepoCharacter->GetActorLocation();
			FireDirection.Z = 0.0f;
		}
	}
	return FireDirection;
}

void AColorepoCharacterController::MoveColorepoCharacter(FVector Movement, FVector FireDirection, float DeltaTime) {
	AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
	// If non-zero size, move this actor
	MyColorepoCharacter->AddMovementInput(Movement, 1000.0f * DeltaTime);
	FRotator direction = FireDirection.Rotation();
	MyColorepoCharacter->SetActorRotation(direction);
}

void AColorepoCharacterController::FireLightBurstDown() {
	UColorepoInstance* ginstance = Cast<UColorepoInstance>(GetGameInstance());
	Levelname = ginstance->CurrentLevel;
	if (Levelname != FString("Main") && Levelname != FString("End")) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		MyColorepoCharacter->FireLightBurstDown();
	}

}

void AColorepoCharacterController::FireLightBurstUp() {
	UColorepoInstance* ginstance = Cast<UColorepoInstance>(GetGameInstance());
	Levelname = ginstance->CurrentLevel;
	if (Levelname != FString("Main") && Levelname != FString("End")) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		MyColorepoCharacter->FireLightBurstUp();
	}
}

void AColorepoCharacterController::xPressed() {
	UColorepoInstance* ginstance = Cast<UColorepoInstance>(GetGameInstance());
	Levelname = ginstance->CurrentLevel;
	if (Levelname != FString("Main") && Levelname != FString("End")) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		MyColorepoCharacter->xPressed();
	}

}

void AColorepoCharacterController::xReleased() {
	UColorepoInstance* ginstance = Cast<UColorepoInstance>(GetGameInstance());
	Levelname = ginstance->CurrentLevel;
	if (Levelname != FString("Main") && Levelname != FString("End")) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		MyColorepoCharacter->xReleased();
	}

}

void AColorepoCharacterController::FireCircle() {
	UColorepoInstance* ginstance = Cast<UColorepoInstance>(GetGameInstance());
	Levelname = ginstance->CurrentLevel;
	if (Levelname != FString("Main") && Levelname != FString("End")) {
		AcolorepoCharacter* MyColorepoCharacter = Cast<AcolorepoCharacter>(GetCharacter());
		MyColorepoCharacter->FireCircle();
	}

}
