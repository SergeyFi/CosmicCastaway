// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
		StatusGetter.Value->UpdateStatus();
	}
	
}

void UStatusComponent::InitStatuses()
{
	for (const auto& StatusGetterClass : StatusGetterClasses)
	{
		StatusGetters.Add(StatusGetterClass, NewObject<UStatusGetter>(GetOwner(), StatusGetterClass));

		if (StatusGetterClass->GetDefaultObject<UStatusGetter>()->GetStatus().bVisible)
		{
			StatusGetterClassesVisible.Add(StatusGetterClass);
		}
	}
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateStatuses();
}

FStatusOutput UStatusComponent::GetStatus(TSubclassOf<UStatusGetter> StatusClass)
{
	auto StatusGetter = StatusGetters.Find(StatusClass);

	if (StatusGetter)
	{
		return (*StatusGetter)->GetStatus();
	}

	return {};
}

TArray<TSubclassOf<UStatusGetter>> UStatusComponent::GetVisibleStatusClasses()
{
	return StatusGetterClassesVisible;
}
