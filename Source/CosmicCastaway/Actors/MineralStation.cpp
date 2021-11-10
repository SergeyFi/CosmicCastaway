// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MineralStation.h"

#include "Components/StationModules/DockModule.h"

// Sets default values
AMineralStation::AMineralStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMineralStation::BeginPlay()
{
	Super::BeginPlay();

	BindToDocks();
}

void AMineralStation::OnDock(APawn* Docker)
{
	MineralsComp = Docker->FindComponentByClass<UMineralsComponent>();
	CreditsComp = Docker->FindComponentByClass<UEnergyCreditComponent>();

	if (MineralsComp && CreditsComp)
	{
		GetWorld()->GetTimerManager().SetTimer
		(ConversionTimer, this, &AMineralStation::Conversion, ConversionRate, true);
	}
	else
	{
		if (!MineralsComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("Minerals component is requared for MineralStation"));
		}

		if (!CreditsComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("Energy credit component is requared for MineralStation"));
		}
	}
}

void AMineralStation::OnUnDock(APawn* Docker)
{
	StopConversion();
}

void AMineralStation::BindToDocks()
{
	TArray<UDockModule*> Docks;
	
	GetComponents<UDockModule>(Docks);
	
	for (auto DockModule : Docks)
	{
		DockModule->OnDock.AddDynamic(this, &AMineralStation::OnDock);
		DockModule->OnUnDock.AddDynamic(this, &AMineralStation::OnUnDock);
	}
}

void AMineralStation::Conversion()
{
	auto MineralsCount = MineralsComp->GetMinerals();
	
	if (MineralsCount > 0.0f)
	{
		auto LocalConversionAmmount = ConversionPerSeconds * ConversionRate;

		if (MineralsCount < LocalConversionAmmount)
		{
			LocalConversionAmmount = MineralsCount;
		}

		MineralsComp->RemoveMinerals(LocalConversionAmmount);

		CreditsComp->AddCredits(LocalConversionAmmount * ConversionCoefficient);
	}
	else
	{
		StopConversion();
	}
}

void AMineralStation::StopConversion()
{
	GetWorld()->GetTimerManager().ClearTimer(ConversionTimer);

	MineralsComp = nullptr;
	CreditsComp = nullptr;
}
