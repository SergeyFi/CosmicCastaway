// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "TargetComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class COSMICCASTAWAY_API UTargetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
};
