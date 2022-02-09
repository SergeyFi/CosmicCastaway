// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ResourcesStorage.h"

// Sets default values for this component's properties
UResourcesStorage::UResourcesStorage()
{
	PrimaryComponentTick.bCanEverTick = false;

}

float UResourcesStorage::AddResource(TSubclassOf<UResource> ResourceClass, float Value)
{
	auto ResExisted = Resources.Find(ResourceClass);
	auto Mass = Value * ResourceClass->GetDefaultObject<UResource>()->GetMolarMass();

	float Remainder = 0.0f;

	if (MassMax != 0.0f)
	{
		auto DiffMass = MassMax - MassCurrent;

		if (Mass > DiffMass)
		{
			Remainder = Value - DiffMass;
			Value = DiffMass;
		}
	}
	
	if (ResExisted == nullptr)
	{
	
		Resources.Add(ResourceClass, {ResourceClass, Value});
	}
	else
	{
		(*ResExisted).Value += Value;
	}

	MassCurrent += Mass;

	return Remainder;
}


// Called when the game starts
void UResourcesStorage::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
