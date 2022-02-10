// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/ShipModules/ShipModule.h"
#include "MiningModule.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FMineInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	float MineRate = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	float MinePerSecond = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	float MineDistance = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	float MineRadius = 100.0f;
};

UCLASS(Blueprintable)
class COSMICCASTAWAY_API UMiningModule : public UShipModule
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Mining")
	FMineInfo GetMineInfo();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	FMineInfo MineInfo;
};
