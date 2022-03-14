// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FLTools.generated.h"

/**
 * 
 */
UCLASS()
class COSMICCASTAWAY_API UFLTools : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Tools")
	static FVector GetRandomSpherePosition();
};
