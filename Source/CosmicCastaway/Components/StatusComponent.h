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
	FStatusOutput GetStatus(TSubclassOf<UStatusGetter> StatusClass);

	UFUNCTION(BlueprintPure, Category = "Statuses")
	TArray<TSubclassOf<UStatusGetter>> GetVisibleStatusClasses();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Statuses")
	TArray<TSubclassOf<UStatusGetter>> StatusGetterClasses;

private:

	UPROPERTY()
	TMap<TSubclassOf<UStatusGetter>, UStatusGetter*> StatusGetters;

	TArray<TSubclassOf<UStatusGetter>> StatusGetterClassesVisible;

	void UpdateStatuses();

	void InitStatuses();
	
};
