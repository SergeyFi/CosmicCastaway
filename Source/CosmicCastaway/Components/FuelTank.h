// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FuelTank.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UFuelTank : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFuelTank();

	UFUNCTION(BlueprintPure, Category = "Fuel")
	float GetCurrentFuel();

	UFUNCTION(BlueprintCallable, Category = "Fuel")
	void RemoveFuel(float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	float FuelMax = 100.0f;

private:

	float FuelCurrent = 100.0f;
		
};
