// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnergyCreditComponent.h"

// Sets default values for this component's properties
UEnergyCreditComponent::UEnergyCreditComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

float UEnergyCreditComponent::AddCredits(float Credits)
{
	CreditsCurrent += Credits;

	if (CreditsCurrent > CreditsMax)
	{
		auto Diff = CreditsCurrent - CreditsMax;

		CreditsCurrent = CreditsMax;

		return Diff;
	}

	return 0.0f;
}

float UEnergyCreditComponent::GetCredits()
{
	return CreditsCurrent;
}

bool UEnergyCreditComponent::IsEmpty()
{
	return CreditsCurrent == 0.0f;
}

void UEnergyCreditComponent::RemoveCredits(float Value)
{
	CreditsCurrent -= Value;

	if (CreditsCurrent < 0.0f)
	{
		CreditsCurrent = 0.0f;
	}
}


// Called when the game starts
void UEnergyCreditComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
