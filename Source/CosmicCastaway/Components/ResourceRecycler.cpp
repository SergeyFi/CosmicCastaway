// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ResourceRecycler.h"

// Sets default values for this component's properties
UResourceRecycler::UResourceRecycler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<FResourceValue> UResourceRecycler::SplitResource(TSubclassOf<UResource> ResClass, float Value)
{
	TArray<FResourceValue> DecompResources;
	
	float EnergyToSplit = ResClass->GetDefaultObject<UResource>()->GetSplittingEnergy() * Value;

	if (EnergyToSplit < EnergyCreditComponent->GetCredits())
	{
		EnergyCreditComponent->RemoveCredits(EnergyToSplit);
		
		for (const auto& Res : ResClass->GetDefaultObject<UResource>()->GetDecompProducts())
		{
			DecompResources.Add({Res.Resource, Res.Value * Value});
		}
	}

	return DecompResources;
}


// Called when the game starts
void UResourceRecycler::BeginPlay()
{
	Super::BeginPlay();

	EnergyCreditComponent = GetOwner()->FindComponentByClass<UEnergyCreditComponent>();
}
