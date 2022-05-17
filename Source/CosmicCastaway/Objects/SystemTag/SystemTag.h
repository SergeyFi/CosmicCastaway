// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SystemTag.generated.h"

/**
 * 
 */
UCLASS(meta = (IsBlueprintBase = "true"))
class COSMICCASTAWAY_API USystemTag : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tag")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tag")
	FLinearColor Color;
};
