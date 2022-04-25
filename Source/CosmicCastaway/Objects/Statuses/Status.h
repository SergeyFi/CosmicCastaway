// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Status.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class COSMICCASTAWAY_API UStatus : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Status")
	bool bInternal = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	FText Status;
};
