// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ClusterLayers/AsteroidLayer.h"

void UAsteroidLayer::GenerateLayer(AActor* Context, float Radius, int Count, FVector Location)
{
	Super::GenerateLayer(Context, Radius, Count, Location);

	if (AsteroidClass && Context)
	{
		for (auto i = 0; i < Count; ++i)
		{
			auto RandomLocation = UFLTools::GetRandomSpherePosition() * Radius;

			FTransform Transform;
			Transform.SetLocation(RandomLocation + Location);

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		
			if (Context->GetWorld())
			{
				Context->GetWorld()->SpawnActor<AActor>(AsteroidClass, Transform, SpawnParameters);
			}
		}
	}
}
