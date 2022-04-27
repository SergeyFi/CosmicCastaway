// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/Statuses/Status.h"
#include "StatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatusDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

	UFUNCTION(BlueprintCallable, Category = "Statuses")
	void AddStatus(TSubclassOf<UStatus> Status);

	UFUNCTION(BlueprintCallable, Category = "Statuses")
	void RemoveStatus(TSubclassOf<UStatus> Status);

	UFUNCTION(BlueprintCallable, Category = "Statuses")
	void UpdateStatus(TSubclassOf<UStatus> Status, FText StatusText);

	UFUNCTION(BlueprintPure, Category = "Statuses")
	FText GetStatusText(TSubclassOf<UStatus> Status);

	UFUNCTION(BlueprintPure, Category = "Statuses")
	bool StatusIsActive(TSubclassOf<UStatus> Status);

	UFUNCTION(BlueprintPure, Category = "Statuses")
	void GetPublicStatuses(TArray<TSubclassOf<UStatus>>& PublicStatuses);

	UFUNCTION(BlueprintPure, Category = "Statuses")
	void GetStatuses(TArray<TSubclassOf<UStatus>>& AllStatuses);

	UPROPERTY(BlueprintAssignable, Category = "Statuses")
	FStatusDelegate OnUpdated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TArray<TSubclassOf<UStatus>> Statuses;
};
