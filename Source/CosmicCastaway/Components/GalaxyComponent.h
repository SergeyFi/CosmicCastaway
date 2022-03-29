// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GalaxyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UGalaxyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGalaxyComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Galaxy")
	float Bound = 450000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Galaxy")
	TSoftObjectPtr<UWorld> InitialLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Galaxy")
	float BrunchChance = 0.5f;

private:

	void CheckPlayerPosition();

	UPROPERTY()
	class ULevelStreamingDynamic* CurrentLevel;

	bool LevelSpawned;
	
	void NewLevel(FVector Direction, TSoftObjectPtr<UWorld>& Level);

	bool Chance();
};
