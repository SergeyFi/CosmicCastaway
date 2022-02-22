// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ShipElements/ShipElement.h"
#include "Objects/ShipModules/MiningModule.h"
#include "MiningElement.generated.h"

/**
 * 
 */
UCLASS()
class COSMICCASTAWAY_API UMiningElement : public UShipElement
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Mining")
	TSubclassOf<UMiningModule> MiningModule;
};
