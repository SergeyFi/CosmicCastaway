// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Resource.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FDecompProduct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UResource> Resource;

	UPROPERTY(EditDefaultsOnly)
	float Weight;
};


UCLASS(Blueprintable, meta = (IsBlueprintBase = "true"))
class COSMICCASTAWAY_API UResource : public UObject
{
	GENERATED_BODY()

public:

	void AddWeight(float Value);
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	FName Name;

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	float Weight;

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	TArray<FDecompProduct> DecompProducts;
};

