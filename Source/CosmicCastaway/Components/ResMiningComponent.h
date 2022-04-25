// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourcesStorage.h"
#include "Actors/Ore.h"
#include "Components/Dock.h"
#include "Components/SceneComponent.h"
#include "Data/ElementsDataTables.h"
#include "ResMiningComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UResMiningComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResMiningComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Mining")
	bool IsMining();

	void SetMiningData(FMiningData* Data);

	UFUNCTION(BlueprintPure, Category = "Mining")
	AOre* GetCurrentMiningOre();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	bool bDebug;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	FText MiningStatusName = FText::FromString("Mining");

	UPROPERTY(EditAnywhere, Category = "Mining|FX")
	float FXScale = 3.0f;

	UFUNCTION()
	void MineSwitch();

	FMiningData MiningData;

private:

	void BindToInput();
	
	bool bMining;

	void MineStop();

	void Mine();

	void Mining(float DeltaTime);
	
	UDock* DockComponent;

	UResourcesStorage* ResourcesStorage;

	UPROPERTY()
	UNiagaraComponent* NiagaraComponent;

	void InitNiagara();

	void StartNiagara();

	void StopNiagara();

	void UpdateStatus();

	AOre* OreCurrent;

	class UStatusComponent* StatusComp;
	
};
