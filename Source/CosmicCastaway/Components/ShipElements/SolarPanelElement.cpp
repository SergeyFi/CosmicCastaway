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
}

void USolarPanelElement::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	EnergyCreditComponent->AddCredits(SolarPanelInfo.SolarEnergyPerSecond * DeltaTime);
}
