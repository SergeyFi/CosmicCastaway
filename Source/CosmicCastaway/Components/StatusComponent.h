// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/Statuses/StatusGetter.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Statuses")
	TArray<UStatusGetter*>& GetStatusGetters();

	UFUNCTION(BlueprintPure, Category = "Statuses")
	TArray<TSubclassOf<UStatusGetter>> GetStatusGetterClasses();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Statuses")
	TArray<TSubclassOf<UStatusGetter>> StatusGetterClasses;

	UPROPERTY()
	TArray<UStatusGetter*> StatusGetters;

private:

	void UpdateStatuses();

	void InitStatuses();

		
};
