// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ShipElements/ShipElement.h"
#include "Components/EnergyCreditComponent.h"
#include "SolarPanelElement.generated.h"

/**
 * 
 */

UCLASS()
class COSMICCASTAWAY_API USolarPanelElement : public UShipElement
{
	GENERATED_BODY()

public:

	USolarPanelElement();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UEnergyCreditComponent* EnergyCreditComponent;

	float EnergyPerSeconds;
};
