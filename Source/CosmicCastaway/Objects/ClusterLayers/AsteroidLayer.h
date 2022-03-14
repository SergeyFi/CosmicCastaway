// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/ClusterLayers/ClusterLayer.h"
#include "AsteroidLayer.generated.h"

/**
 * 
 */
UCLASS()
class COSMICCASTAWAY_API UAsteroidLayer : public UClusterLayer
{
	GENERATED_BODY()

public:

	virtual void GenerateLayer(AActor* Context, float Radius, int Count, FVector Location) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Layer|Asteroid")
	TSubclassOf<AActor> AsteroidClass;
};
