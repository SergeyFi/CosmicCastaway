// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourcesStorage.h"
#include "Components/ActorComponent.h"
#include "Data/ElementsDataTables.h"
#include "RocketEngine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API URocketEngine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URocketEngine();
	
	// Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Engine")
	void StartEngine();

	UFUNCTION(BlueprintCallable, Category = "Engine")
	void StopEngine();
	
	void SetEngineData(FEngineData* Data);

	UFUNCTION(BlueprintPure, Category = "Engine")
	const TArray<FResourceValue>& GetFuelType();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	
	UPrimitiveComponent* OwnerRoot;

	UInputComponent* InputComponent;

	bool bFullStop;

	float FuelWasteCoefficient = 8000.0f;

	float ThrustCoefficient = 150.0f;

	void GetOwnerRoot();

	void AddEngineForce(float DeltaTime);

	void BindToInput();

	UFUNCTION()
	void FullStopTrue();

	UFUNCTION()
	void FullStopFalse();

	void FullStop(float DeltaTime);
	
	void FuelWaste(float Amount);

	void AddShuntingEnginesForce(float DeltaTime);
	
	FEngineData EngineData;

	UResourcesStorage* ResStorage;
};
