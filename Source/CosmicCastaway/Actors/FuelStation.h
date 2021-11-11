// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EnergyCreditComponent.h"
#include "Components/FuelTank.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SleepInterface.h"
#include "FuelStation.generated.h"

UCLASS()
class COSMICCASTAWAY_API AFuelStation : public AActor, public ISleepInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuelStation();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Sleep() override;

	virtual void WakeUp() override;

	virtual bool IsSleep() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "FuelStation")
	float RotationRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "FuelStation")
	float RefuelingRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "FuelStation")
	float RefuelingPerSecond = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "FuelStation")
	float ConversionCoefficient = 1.0f;
	
private:

	bool bIsSleep;

	UFuelTank* FuelTank;

	UEnergyCreditComponent* CreditComponent;

	FTimerHandle TimerRefueling;

	void BindToDocks();

	UFUNCTION()
	void OnDock(APawn* Docker);

	UFUNCTION()
	void OnUnDock(APawn* Docker);
	
	void StartRefueling();

	void Refueling();

	void StopRefueling();
};
