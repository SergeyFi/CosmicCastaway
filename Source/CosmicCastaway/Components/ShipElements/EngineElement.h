// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ShipElements/ShipElement.h"
#include "EngineElement.generated.h"

/**
 * 
 */
UCLASS()
class COSMICCASTAWAY_API UEngineElement : public UShipElement
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
