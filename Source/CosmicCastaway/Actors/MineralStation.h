// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EnergyCreditComponent.h"
#include "GameFramework/Actor.h"
#include "Components/MineralsComponent.h"
#include "MineralStation.generated.h"

UCLASS()
class COSMICCASTAWAY_API AMineralStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMineralStation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "MineralStation")
	float ConversionRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "MineralStation")
	float ConversionPerSeconds = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "MineralStation")
	float ConversionCoefficient = 1.0f;

private:

	UFUNCTION()
	void OnDock(APawn* Docker);

	UFUNCTION()
	void OnUnDock(APawn* Docker);

	void BindToDocks();

	void Conversion();

	void StopConversion();

	void RandomRotation();

	FTimerHandle ConversionTimer;

	UMineralsComponent* MineralsComp;

	UEnergyCreditComponent* CreditsComp;
};
