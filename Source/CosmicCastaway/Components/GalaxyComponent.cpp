// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GalaxyComponent.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGalaxyComponent::UGalaxyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGalaxyComponent::BeginPlay()
{
	Super::BeginPlay();

	GenerateSystems();
}

void UGalaxyComponent::GenerateSystems()
{
	SystemsWarpData.Empty();

	if (SystemsDataTable)
	{
		TArray<FSystemData*> SystemsData;
		SystemsDataTable->GetAllRows<FSystemData>("SystemsDataImportFail", SystemsData);

		auto LastIndex = SystemsData.Num() - 1;
		for (auto i = 0; i < LastIndex; ++i)
		{
			auto RandIndex = FMath::RandRange(0, LastIndex);

			if (i != RandIndex)
			{
				SystemsData.Swap(i, RandIndex);
			}
		}

		for (const auto& SystemData : SystemsData)
		{
			if (SystemsWarpData.Num() >= MaxSystemsCount)
			{
				return;
			}

			SystemsWarpData.Add(SystemData->WarpData);
		}
	}
}

const TArray<FWarpData>& UGalaxyComponent::GetSystems()
{
	return SystemsWarpData;
}

void UGalaxyComponent::WarpToSystem(int32 SystemIndex)
{
	if (SystemsWarpData.Num() > SystemIndex)
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetOwner(), SystemsWarpData[SystemIndex].Map);
	
		GenerateSystems();
	}
	

}
