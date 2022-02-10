// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnergyCreditComponent.h"
#include "Components/ActorComponent.h"
#include "Objects/Resources/Resource.h"
#include "ResourceRecycler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UResourceRecycler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceRecycler();

	UFUNCTION(BlueprintCallable, Category = "Resource")
	TArray<FResourceValue> SplitResource(TSubclassOf<UResource> ResClass, float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UEnergyCreditComponent* EnergyCreditComponent;

		
};
