// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "Objects/SystemTag/SystemTag.h"
#include "GalaxyComponent.generated.h"

USTRUCT(BlueprintType)
struct FWarpData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TSoftObjectPtr<UWorld> Map;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int32 SystemSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float WarpFuel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TArray<TSubclassOf<USystemTag>> Tags;
};

USTRUCT(BlueprintType)
struct FSystemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	FWarpData WarpData;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UGalaxyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGalaxyComponent();

	UFUNCTION(BlueprintPure, Category = "Galaxy")
	const TArray<FWarpData>& GetSystems();

	UFUNCTION(BlueprintCallable, Category = "Galaxy")
	void WarpToSystem(int32 SystemIndex);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Galaxy")
	UDataTable* SystemsDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Galaxy")
	int32 MaxSystemsCount = 3;

private:

	void GenerateSystems();

	TArray<FWarpData> SystemsWarpData;
};
