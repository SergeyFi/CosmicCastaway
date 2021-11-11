// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FuelStation.h"

#include "Components/StationModules/DockModule.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFuelStation::AFuelStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFuelStation::Sleep()
{
	SetActorTickEnabled(false);
	bIsSleep = true;
}

void AFuelStation::WakeUp()
{
	SetActorTickEnabled(true);
	bIsSleep = false;
}

bool AFuelStation::IsSleep()
{
	return bIsSleep;
}

// Called when the game starts or when spawned
void AFuelStation::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(UKismetMathLibrary::RandomRotator());

	Sleep();

	BindToDocks();
}

void AFuelStation::BindToDocks()
{
	TArray<UDockModule*> Docks;

	GetComponents<UDockModule>(Docks);

	for (auto Dock : Docks)
	{
		Dock->OnDock.AddDynamic(this, &AFuelStation::OnDock);
		Dock->OnUnDock.AddDynamic(this, &AFuelStation::OnUnDock);
	}
}

void AFuelStation::OnDock(APawn* Docker)
{
	FuelTank = Docker->FindComponentByClass<UFuelTank>();
	CreditComponent = Docker->FindComponentByClass<UEnergyCreditComponent>();

	if (FuelTank && CreditComponent)
	{
		StartRefueling();
	}
	else
	{
		if (!FuelTank)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fuelst station is requared FuelTankComponent"));
		}

		if (!CreditComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fuelst station is requared EnergyCreditComponent"));
		}
	}
}

void AFuelStation::OnUnDock(APawn* Docker)
{
	StopRefueling();
}

void AFuelStation::StartRefueling()
{
	GetWorld()->GetTimerManager().SetTimer
	(TimerRefueling, this, &AFuelStation::Refueling, RefuelingRate, true);
}

void AFuelStation::Refueling()
{
	if (!FuelTank->IsFull() && !CreditComponent->IsEmpty())
	{
		auto Fuel = RefuelingRate * RefuelingPerSecond;
		auto FuelPrice = Fuel * ConversionCoefficient;
		auto BuyerCredits = CreditComponent->GetCredits();

		if (BuyerCredits < FuelPrice)
		{
			Fuel *= BuyerCredits / FuelPrice;
			FuelPrice = Fuel * ConversionCoefficient;
		}

		auto RemainingFuel = FuelTank->GetFuelMax() - FuelTank->GetCurrentFuel();
		
		if (RemainingFuel < Fuel)
		{
			Fuel = RemainingFuel;
			FuelPrice = Fuel * ConversionCoefficient;
		}
		
		FuelTank->AddFuel(Fuel);
		CreditComponent->RemoveCredits(FuelPrice);
	}
	else
	{
		StopRefueling();
	}
}

void AFuelStation::StopRefueling()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerRefueling);
	FuelTank = nullptr;
}

// Called every frame
void AFuelStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation({0.0f, RotationRate * DeltaTime, 0.0f});
}
