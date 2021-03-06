// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	InitStatuses();
}

void UStatusComponent::UpdateStatuses()
{
	for (const auto& StatusGetter : StatusGetters)
	{
		StatusGetter->UpdateStatus();
	}
}

void UStatusComponent::InitStatuses()
{
	for (const auto& StatusGetterClass : StatusGetterClasses)
	{
		StatusGetters.Add(NewObject<UStatusGetter>(GetOwner(), StatusGetterClass));
	}
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateStatuses();
}

TArray<UStatusGetter*>& UStatusComponent::GetStatusGetters()
{
	return StatusGetters;
}

TArray<TSubclassOf<UStatusGetter>> UStatusComponent::GetStatusGetterClasses()
{
	return StatusGetterClasses;
}

