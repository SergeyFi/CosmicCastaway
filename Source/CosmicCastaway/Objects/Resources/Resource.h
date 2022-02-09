// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Resource.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FResourceValue
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UResource> Resource;

	UPROPERTY(EditDefaultsOnly)
	float Value;
};

UCLASS(Blueprintable, meta = (IsBlueprintBase = "true"))
class COSMICCASTAWAY_API UResource : public UObject
{
	GENERATED_BODY()

public:

	float GetMolarMass();
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	FName Name;

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	float MolarMass;

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	TArray<TSubclassOf<UResource>> DecompProducts;
};

