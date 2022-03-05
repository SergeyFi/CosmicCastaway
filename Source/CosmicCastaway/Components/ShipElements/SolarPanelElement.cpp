// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipElements/SolarPanelElement.h"

USolarPanelElement::USolarPanelElement()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USolarPanelElement::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(true);

	EnergyCreditComponent = GetOwner()->FindComponentByClass<UEnergyCreditComponent>();

	if (DataTable)
	{
		FString Message;
		auto DataPtr = DataTable->FindRow<FSolarPanelsData>(DataID, Message);

		if (DataPtr)
		{
			EnergyPerSeconds = DataPtr->EnergyPerSeconds;
		}
	}
}

void USolarPanelElement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	EnergyCreditComponent->AddCredits(EnergyPerSeconds * DeltaTime);
}
