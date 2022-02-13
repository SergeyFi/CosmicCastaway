// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OxygenComponent.h"

// Sets default values for this component's properties
UOxygenComponent::UOxygenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOxygenComponent::BeginPlay()
{
	Super::BeginPlay();

	ResStorage = GetOwner()->FindComponentByClass<UResourcesStorage>();
}


// Called every frame
void UOxygenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ResStorage->RemoveResource(OxygenClass, DeltaTime * OxygenWastePerSeconds);
}

float UOxygenComponent::GetCurrentOxygen()
{
	return ResStorage->GetResource(OxygenClass);
}

