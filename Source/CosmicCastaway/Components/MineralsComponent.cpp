// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MineralsComponent.h"

// Sets default values for this component's properties
UMineralsComponent::UMineralsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UMineralsComponent::AddMinerals(float Value)
{
	Minerals += Value;

	if (Minerals > MaxMinerals)
	{
		Minerals = MaxMinerals;
	}
}

void UMineralsComponent::RemoveMinerals(float Value)
{
	Minerals -= Value;

	if (Minerals < 0.0f)
	{
		Minerals = 0.0f;
	}
}

bool UMineralsComponent::MineralsIsFull()
{
	return Minerals == MaxMinerals;
}

float UMineralsComponent::GetMinerals()
{
	return Minerals;
}


// Called when the game starts
void UMineralsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
