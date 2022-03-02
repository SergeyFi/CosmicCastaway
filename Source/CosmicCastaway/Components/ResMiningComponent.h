// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourcesStorage.h"
#include "Components/Dock.h"
#include "Components/SceneComponent.h"
#include "Objects/ShipModules/MiningModule.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
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

	UFUNCTION(BlueprintCallable, Category = "Mining")
	void SetMiningModule(TSubclassOf<UMiningModule> Module);

	UFUNCTION(BlueprintPure, Category = "Mining")
	bool IsMining();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(EditAnywhere, Category = "Mining")
	TSubclassOf<UMiningModule> MiningModule;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	bool bDebug;

	UPROPERTY(EditAnywhere, Category = "Mining|FX")
	UNiagaraSystem* NiagaraFX;

	UPROPERTY(EditAnywhere, Category = "Mining|FX")
	float FXScale = 3.0f;

	UFUNCTION()
	void MineSwitch();

private:

	void BindToInput();
	
	bool bMining;

	void MineStop();

	void Mine();

	void UpdateMining();

	FMineInfo MineInfo;

	void Mining(float DeltaTime);
	
	UDock* DockComponent;

	UResourcesStorage* ResourcesStorage;

	UPROPERTY()
	UNiagaraComponent* NiagaraComponent;

	void InitNiagara();

	void StartNiagara();

	void StopNiagara();
	
};
