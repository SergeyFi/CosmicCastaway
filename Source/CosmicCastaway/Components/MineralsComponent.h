// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MineralsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UMineralsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMineralsComponent();

	UFUNCTION(BlueprintCallable, Category = "Minerals")
	void AddMinerals(float Value);

	UFUNCTION(BlueprintPure, Category = "Minerals")
	bool MineralsIsFull();

	UFUNCTION(BlueprintPure, Category = "Minerals")
	float GetMinerals();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Minerals")
	float MaxMinerals = 100.0f;
	
private:

	float Minerals = 0.0f;
};
