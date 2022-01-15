// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/Resources/Resource.h"
#include "ResourcesStorage.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UResourcesStorage : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourcesStorage();

	// Will return remainder
	UFUNCTION(BlueprintCallable, Category = "Resources")
	float AddResource(TSubclassOf<UResource> ResourceClass, float Weight);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<UResource>,UResource*> Resources;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resources")
	float WeightCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	float WeightMax;
};
