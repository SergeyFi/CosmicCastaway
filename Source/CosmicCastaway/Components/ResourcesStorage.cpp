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

	if (Value <= 0.0f)
	{
		return 0.0f;
	}
	
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

float UResourcesStorage::AddResourceByValue(FResourceValue Value)
{
	return AddResource(Value.Resource, Value.Value);
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
		if (*Res - Value > 0.0f)
		{
			*Res -= Value;

			MassCurrent -= GetResourceMass(ResourceClass, Value);
		}
		else
		{
			MassCurrent -= GetResourceMass(ResourceClass, *Res);
			*Res = 0.0f;
		}

		if (*Res == 0.0f)
		{
			Resources.Remove(ResourceClass);
		}
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

TArray<TSubclassOf<UResource>> UResourcesStorage::GetResourcesClasses()
{
	TArray<TSubclassOf<UResource>> ResourceClasses;

	for (auto Res : Resources)
	{
		ResourceClasses.Add(Res.Key);
	}

	return ResourceClasses;
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
