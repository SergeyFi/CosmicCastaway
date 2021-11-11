// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FuelTank.h"

// Sets default values for this component's properties
UFuelTank::UFuelTank()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

float UFuelTank::GetCurrentFuel()
{
	return FuelCurrent;
}

bool UFuelTank::IsFull()
{
	return FuelCurrent == FuelMax;
}

void UFuelTank::RemoveFuel(float Value)
{
	FuelCurrent -= Value;

	if (FuelCurrent < 0.0f)
	{
		FuelCurrent = 0.0f;
	}
}

void UFuelTank::AddFuel(float Value)
{
	FuelCurrent += Value;

	if (FuelCurrent > FuelMax)
	{
		FuelCurrent = FuelMax;
	}
}

float UFuelTank::GetFuelMax()
{
	return FuelMax;
}


// Called when the game starts
void UFuelTank::BeginPlay()
{
	Super::BeginPlay();
	
}
