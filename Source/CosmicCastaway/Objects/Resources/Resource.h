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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UResource> Resource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Value;
};

UCLASS(Blueprintable, meta = (IsBlueprintBase = "true"))
class COSMICCASTAWAY_API UResource : public UObject
{
	GENERATED_BODY()

public:

	float GetMolarMass();

	const TArray<FResourceValue>& GetDecompProducts();

	float GetSplittingEnergy();
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources")
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources")
	float MolarMass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources")
	float SplittingEnergy = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources")
	TArray<FResourceValue> DecompProducts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources")
	FColor Color;
};

