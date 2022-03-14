// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/ClusterLayers/ClusterLayer.h"
#include "Cluster.generated.h"

UCLASS(Blueprintable)
class COSMICCASTAWAY_API ACluster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACluster();

	float GetClusterRadius();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Cluster")
	TArray<FClusterLayerData> ClustersData;

private:

	void GenerateLayers();

};
