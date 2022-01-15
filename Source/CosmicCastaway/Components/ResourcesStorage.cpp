// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ResourcesStorage.h"

// Sets default values for this component's properties
UResourcesStorage::UResourcesStorage()
{
	PrimaryComponentTick.bCanEverTick = false;

}

float UResourcesStorage::AddResource(TSubclassOf<UResource> ResourceClass, float Weight)
{
	auto ResExisted = Resources.Find(ResourceClass);

	float Remainder = 0.0f;

	if (WeightMax != 0.0f)
	{
		auto Diff = WeightMax - WeightCurrent;

		if (Weight > Diff)
		{
			Remainder = Weight - Diff;
			Weight = Diff;
		}
	}
	
	if (ResExisted == nullptr)
	{
		auto Resource = NewObject<UResource>(GetOwner(), ResourceClass);
		Resource->AddWeight(Weight);
	
		Resources.Add(ResourceClass, Resource);
	}
	else
	{
		(*ResExisted)->AddWeight(Weight);
	}

	return Remainder;
}


// Called when the game starts
void UResourcesStorage::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
