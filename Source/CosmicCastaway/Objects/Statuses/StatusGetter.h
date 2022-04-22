// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatusGetter.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable)
struct FStatusOutput
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	FText Status;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	bool bActive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Status")
	bool bVisible;
};

UCLASS(Blueprintable)
class COSMICCASTAWAY_API UStatusGetter : public UObject
{
	GENERATED_BODY()

public:

	virtual void UpdateStatus();

	UFUNCTION(BlueprintPure, Category = "Status")
	FStatusOutput GetStatus();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Status")
	FStatusOutput Status;
};
