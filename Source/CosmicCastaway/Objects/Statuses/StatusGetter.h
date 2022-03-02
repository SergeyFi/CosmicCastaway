// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatusGetter.generated.h"

/**
 * 
 */

UENUM(Blueprintable)
enum class EStatusVisibility: uint8
{
	Hide		UMETA(DisplayName = "Hide"),
	Display     UMETA(DisplayName = "Display")
};

USTRUCT(Blueprintable)
struct FStatusOutput
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	FText Status;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	EStatusVisibility StatusVisibility;
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

	FStatusOutput Status;
};
