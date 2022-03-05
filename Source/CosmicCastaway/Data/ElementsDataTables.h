// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Objects/Resources/Resource.h"
#include "NiagaraComponent.h"
#include "ElementsDataTables.generated.h"

USTRUCT(BlueprintType)
struct FElementData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	UStaticMesh* Mesh;
};

USTRUCT(BlueprintType)
struct FSolarPanelsData : public FElementData
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float  EnergyPerSeconds;
};

USTRUCT(BlueprintType)
struct FEngineData : public FElementData
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float Thrust;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float ShuntinThrust;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float ThrustFullStop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float EngineThrustEfficiency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float EngineFullStopEfficiency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TArray<FResourceValue> Fuel;
};

USTRUCT(BlueprintType)
struct FMiningData : public FElementData
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float MineRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float MinePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float MineDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float MineRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	UNiagaraSystem* NiagaraFX;
};