// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Cluster.h"

// Sets default values
ACluster::ACluster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACluster::BeginPlay()
{
	Super::BeginPlay();

	GenerateLayers();
}

void ACluster::GenerateLayers()
{
	for (auto& Data : ClustersData)
	{
		if (Data.ClusterLayer)
		{
			Data.ClusterLayer->GetDefaultObject<UClusterLayer>()->
			GenerateLayer(this, Data.Radius, Data.Count, GetActorLocation());
		}
	}
}
