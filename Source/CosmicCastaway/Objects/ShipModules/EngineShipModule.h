// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Resources/Resource.h"
#include "Objects/ShipModules/ShipModule.h"
#include "EngineShipModule.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FEngineProperties
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	float Thrust = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	float ShuntinThrust = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	float ThrustFullStop = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	float EngineThrustEfficiency = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	float EngineFullStopEfficiency = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	TArray<FResourceValue> Fuel;
};

UCLASS(Blueprintable)
class COSMICCASTAWAY_API UEngineShipModule : public UShipModule
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Engine")
	FEngineProperties GetEngineProperties();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	FEngineProperties EngineProperties;
};
