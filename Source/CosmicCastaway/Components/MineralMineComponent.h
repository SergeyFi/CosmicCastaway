// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dock.h"
#include "MineralsComponent.h"
#include "Components/SceneComponent.h"
#include "MineralMineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UMineralMineComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMineralMineComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Mine();

	void MineStop();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	float MineRate = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	float MinePerSecond = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	float MineDistance = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	float MineRadius = 100.0f;

private:

	void Mining(float DeltaTime);

	void BindToInput();

	void MineSwitch();

	UDock* DockComponent;

	UMineralsComponent* MineralsComp;

	bool bMining;
};
