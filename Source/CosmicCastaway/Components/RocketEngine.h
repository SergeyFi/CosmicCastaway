// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FuelTank.h"
#include "Components/ActorComponent.h"
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	float Thrust = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	float ThrustFullStop = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	float EngineThrustEfficiency = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Engine");
	float EngineFullStopEfficiency = 1.0f;
	
private:
	
	UPrimitiveComponent* OwnerRoot;

	UInputComponent* InputComponent;

	UFuelTank* FuelTank;

	bool bFullStop;

	float Coefficient = 8000.0f;

	void GetOwnerRoot();

	void AddEngineForce(float DeltaTime);

	void BindToInput();

	UFUNCTION()
	void FullStopTrue();

	UFUNCTION()
	void FullStopFalse();

	void FullStop(float DeltaTime);

	void FindFuelTank();

	void FuelWaste(float Amount);
};
