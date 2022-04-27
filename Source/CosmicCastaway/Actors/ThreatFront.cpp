// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ThreatFront.h"

// Sets default values
AThreatFront::AThreatFront()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxDetector"));
	BoxDetector->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AThreatFront::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThreatFront::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

