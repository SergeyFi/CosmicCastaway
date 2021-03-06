// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/Resources/Resource.h"
#include "Ore.generated.h"



UCLASS(Blueprintable)
class COSMICCASTAWAY_API AOre : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOre();

	FResourceValue MineResource(float Value);

	UFUNCTION(BlueprintPure, Category = "Ore")
	float GetResourcesCountInPercent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Ore")
	FResourceValue Resource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ore")
	UStaticMeshComponent* OreMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Ore")
	float ScaleMin = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "Ore")
	float ScaleMax = 0.6f;

	UPROPERTY(EditDefaultsOnly, Category = "Ore")
	float ZOffset = 30.0f;

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyOre();

	void RandomRangeScale();

private:

	UMaterialInstanceDynamic* DynamicMaterial;

	float InitialResValue;
};
