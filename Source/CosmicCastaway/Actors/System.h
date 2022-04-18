// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Cluster.h"
#include "System.generated.h"

UCLASS()
class COSMICCASTAWAY_API ASystem : public APointInterest
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere, Category = "System")
	TArray<TSubclassOf<ACluster>> ClusterClasses;

	UPROPERTY(EditAnywhere, Category = "System")
	float SystemRadius;

private:

	void SpawnCluster(TSubclassOf<ACluster> ClasterClass, FVector Location);

	void SpawnClusters();

	FVector GetSystemSpawnLocation(TSubclassOf<ACluster> ClusterClass);

	UPROPERTY()
	TArray<ACluster*> Clusters;
};
