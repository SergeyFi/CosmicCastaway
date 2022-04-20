// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WarpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UWarpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWarpComponent();

	UFUNCTION(BlueprintCallable, Category = "Warp")
	void Warp(AActor* NewTarget);

	UFUNCTION(BlueprintPure, Category = "Warp")
	bool IsWarping();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Warp")
	float WarpEnergy = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Warp")
	float WarpMaxSpeed = 90000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Warp")
	float WarpStopDistance = 80000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Warp")
	float WarpStopForce = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Warp")
	float WarpStopSpeed = 10.0f;

private:

	bool bWarping;

	void StopWarping();

	void Warping(float DeltaTime);

	UPrimitiveComponent* OwnerRoot;
	
	FVector WarpTargetDirection;

	float WarpEnergyCoefficient = 10000.0f;

	float WarpDistanceInitial;

	AActor* Target;
};
