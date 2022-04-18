// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/System.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/GameStateCosmic.h"
#include "Tools/FLTools.h"

// Sets default values
ASystem::ASystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASystem::BeginPlay()
{
	Super::BeginPlay();

	SpawnClusters();

	auto GameState = Cast<AGameStateCosmic>( UGameplayStatics::GetGameState(this));

	if (GameState)
	{
		GameState->AddSystem(this);
	}
}

void ASystem::BeginDestroy()
{
	Super::BeginDestroy();

	auto GameState = Cast<AGameStateCosmic>( UGameplayStatics::GetGameState(this));

	if (GameState)
	{
		GameState->RemoveSystem(this);
	}
}

void ASystem::SpawnCluster(TSubclassOf<ACluster> ClasterClass, FVector Location)
{
	FTransform Transform;
	Transform.SetLocation(Location);
	
	Clusters.Add(GetWorld()->SpawnActor<ACluster>(ClasterClass, Transform));
}

void ASystem::SpawnClusters()
{
	for (auto& ClusterClass : ClusterClasses)
	{
		SpawnCluster(ClusterClass, GetSystemSpawnLocation(ClusterClass));
	}
}

FVector ASystem::GetSystemSpawnLocation(TSubclassOf<ACluster> ClusterClass)
{
	auto ClusterRadius = ClusterClass->GetDefaultObject<ACluster>()->GetClusterRadius();
	
	FVector DesiredLocation;

	auto IsOverlap = true;

	auto Count = 0;

	while (IsOverlap && Count < 30)
	{
		IsOverlap = false;
		
		DesiredLocation = UFLTools::GetRandomSpherePosition() * SystemRadius + GetActorLocation();
		
		for (auto& Cluster : Clusters)
		{
			if (Cluster->GetActorLocation().Equals(DesiredLocation, Cluster->GetClusterRadius() * 1.5f))
			{
				IsOverlap = true;
			}
		}

		Count++;
	}
	
	return DesiredLocation;
}
