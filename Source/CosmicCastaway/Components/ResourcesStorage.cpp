// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ResourcesStorage.h"

// Sets default values for this component's properties
UResourcesStorage::UResourcesStorage()
{
	PrimaryComponentTick.bCanEverTick = false;

}

float UResourcesStorage::AddResource(TSubclassOf<UResource> ResourceClass, float Value)
{
	auto Remainder = 0.0f;
	
	if (ResourceClass)
	{
		auto ResourceMass = GetResourceMass(ResourceClass, Value);

		auto ExcessMass = MassMax - (ResourceMass + MassCurrent);

		if (ExcessMass < 0.0f)
		{
			ExcessMass *= -1.0f;

			Remainder = Value * (ExcessMass / ResourceMass);
			Value -= Remainder;

			ResourceMass -= ExcessMass;
		}

		auto Res = Resources.Find(ResourceClass);

		if (Res)
		{
			*Res += Value;
		}
		else
		{
			Resources.Add(ResourceClass, Value);
		}

		MassCurrent += ResourceMass;
	}

	return Remainder;
}

float UResourcesStorage::GetResource(TSubclassOf<UResource> ResourceClass)
{
	auto Res = Resources.Find(ResourceClass);
	
	if (Res)
	{
		return *Res;
	}
	
	return 0.0f;
}

void UResourcesStorage::RemoveResource(TSubclassOf<UResource> ResourceClass, float Value)
{
	auto Res = Resources.Find(ResourceClass);
	
	if (Res)
	{
		*Res -= Value;

		MassCurrent -= GetResourceMass(ResourceClass, Value);
	}
}

float UResourcesStorage::GetMassCurrent()
{
	return MassCurrent;
}

float UResourcesStorage::GetMassMax()
{
	return MassMax;
}


// Called when the game starts
void UResourcesStorage::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

float UResourcesStorage::GetResourceMass(TSubclassOf<UResource> ResClass, float Value)
{
	return (ResClass->GetDefaultObject<UResource>()->GetMolarMass() / MassCoefficient) * Value;
}
