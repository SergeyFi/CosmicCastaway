// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tools/FLTools.h"
#include "ClusterLayer.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FClusterLayerData
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	float Radius;

	UPROPERTY(EditAnywhere)
	int Count;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UClusterLayer> ClusterLayer;
};

UCLASS(Blueprintable)
class COSMICCASTAWAY_API UClusterLayer : public UObject
{
	GENERATED_BODY()

public:

	virtual void GenerateLayer(AActor* Context ,float Radius, int Count, FVector Location);
};
