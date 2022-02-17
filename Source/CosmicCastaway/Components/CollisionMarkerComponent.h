// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollisionDetectorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CollisionMarkerComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent = "true"))
class COSMICCASTAWAY_API UCollisionMarkerComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UCollisionMarkerComponent();
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Marker")
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Marker")
	UMaterialInterface* CollisionMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Marker")
	float Length = 10000.0f;

private:

	UCollisionDetectorComponent* CollisionDetector;
};
