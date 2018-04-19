// Fill out your copyright notice in the Description page of Project Settings.

#include "colorepo.h"
#include "Crystal.h"
#include "Engine.h"


// Sets default values
ACrystal::ACrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoundingBox;

}


// Called when the game starts or when spawned
void ACrystal::BeginPlay()
{
	Super::BeginPlay();
	PlayerOne = Cast<AcolorepoCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerTwo = Cast<AcolorepoCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 1));
	
}



// Called every frame
void ACrystal::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (PlayerOne != nullptr) {
		if (BoundingBox->IsOverlappingActor(PlayerOne)) {
			//If player1 is overlapping me, destroy and update color
			if (PlayerOne->DoDestroy) {
				PlayerOne->ColorOnDeck = CrystalColor;
				BeingDestroyed(CrystalColor);
				this->Destroy();
			}
		}
		else {
		}
	}
	if (PlayerTwo != nullptr) {
		if (BoundingBox->IsOverlappingActor(PlayerTwo)) {
			//If player2 is overlapping me, destroy and update color
			if (PlayerTwo->DoDestroy) {
				PlayerTwo->ColorOnDeck = CrystalColor;
				BeingDestroyed(CrystalColor);
				this->Destroy();
			}
		}
		else {
		}
	}

}

