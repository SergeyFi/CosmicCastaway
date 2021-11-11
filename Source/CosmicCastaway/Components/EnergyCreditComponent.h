// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnergyCreditComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UEnergyCreditComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergyCreditComponent();

	UFUNCTION(BlueprintCallable, Category = "Credits")
	float AddCredits(float Credits);

	UFUNCTION(BlueprintPure, Category = "Credits")
	float GetCredits();

	UFUNCTION(BlueprintPure, Category = "Credits")
	bool IsEmpty();

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void RemoveCredits(float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, Category = "Credits")
	float CreditsMax = 5000.0f;
private:

	float CreditsCurrent;
		
};
