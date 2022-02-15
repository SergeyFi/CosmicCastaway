// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourcesStorage.h"
#include "Components/Dock.h"
#include "Components/SceneComponent.h"
#include "Objects/ShipModules/MiningModule.h"
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(EditAnywhere, Category = "Mining")
	TSubclassOf<UMiningModule> MiningModule;

	UPROPERTY(EditAnywhere, Category = "Mining")
	bool bDebug;

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
	
};
