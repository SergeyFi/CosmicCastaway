// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/Resources/Resource.h"
#include "EnergyCreditComponent.h"
#include "ResourcesStorage.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UResourcesStorage : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourcesStorage();

	UFUNCTION(BlueprintCallable, Category = "Resources")
	float AddResource(TSubclassOf<UResource> ResourceClass, float Value);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	float AddResourceByValue(FResourceValue Value);

	UFUNCTION(BlueprintPure, Category = "Resources")
	float GetResource(TSubclassOf<UResource> ResourceClass);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void RemoveResource(TSubclassOf<UResource> ResourceClass, float Value);

	UFUNCTION(BlueprintPure, Category = "Resources")
	float GetMassCurrent();

	UFUNCTION(BlueprintPure, Category = "Resources")
	float GetMassMax();

	UFUNCTION(BlueprintPure, Category = "Resources")
	TArray<TSubclassOf<UResource>> GetResourcesClasses();

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void SplitResource(TSubclassOf<UResource> ResourceClass, float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TArray<FResourceValue> ResourcesDefault;
	
	TMap<TSubclassOf<UResource>, float> Resources;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resources")
	float MassCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	float MassMax = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	float MassCoefficient = 100.0f;

	float GetResourceMass(TSubclassOf<UResource> ResClass, float Value);

	UPROPERTY(EditDefaultsOnly,  Category = "Resources")
	float ConversionSpeed = 9.0f;

private:
	
	UEnergyCreditComponent* EnergyCreditComponent;

	void AddDefaultResources();
};
