// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourcesStorage.h"
#include "Components/ActorComponent.h"
#include "OxygenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UOxygenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOxygenComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Oxygen")
	float GetCurrentOxygen();

	UFUNCTION(BlueprintPure, Category = "Oxygen")
	float GetWastePerSeconds();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Oxygen")
	TSubclassOf<UResource> OxygenClass;

	UPROPERTY(EditDefaultsOnly, Category = "Oxygen")
	float OxygenWastePerSeconds = 0.1f;

private:

	UResourcesStorage* ResStorage;
		
};
