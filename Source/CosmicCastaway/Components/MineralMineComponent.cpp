// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MineralMineComponent.h"
#include "HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actors/Mineral.h"

// Sets default values for this component's properties
UMineralMineComponent::UMineralMineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = MineRate;
}

void UMineralMineComponent::Mine()
{
	bMining = true;
	SetComponentTickEnabled(true);
}

void UMineralMineComponent::MineStop()
{
	bMining = false;
	SetComponentTickEnabled(false);
	GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Blue, TEXT("Mine stop"));
}


// Called when the game starts
void UMineralMineComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);

	DockComponent = GetOwner()->FindComponentByClass<UDock>();
	MineralsComp = GetOwner()->FindComponentByClass<UMineralsComponent>();

	BindToInput();
}

void UMineralMineComponent::Mining(float DeltaTime)
{
	if (DockComponent)
	{
		if (!DockComponent->IsDock())
		{
			MineStop();
			return;
		}
	}

	TArray<FHitResult> HitResults;

	auto bHit = UKismetSystemLibrary::SphereTraceMulti
	(
		GetOwner(),
		GetComponentLocation(),
		GetComponentLocation() + GetForwardVector() * MineDistance,
		MineRadius,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		{},
		EDrawDebugTrace::None,
		HitResults,
		true
	);

	if (bHit)
	{
		bool bMineralAvailable = false;
		for (auto HitResult : HitResults)
		{
			auto Mineral = Cast<AMineral>(HitResult.GetActor());
		
			if (Mineral)
			{
				bMineralAvailable = true;

				if (!MineralsComp->MineralsIsFull())
				{
					auto MineralHealth = Mineral->FindComponentByClass<UHealthComponent>();

					if (MineralHealth)
					{
						MineralHealth->RemoveHealth(MinePerSecond * DeltaTime);

						if (MineralHealth->GetHealth() == 0.0f)
						{
							MineStop();
							return;
						}
					}

					MineralsComp->AddMinerals(MinePerSecond * DeltaTime);
				}
			}
		}

		if (!bMineralAvailable)
		{
			MineStop();
		}
	}
}

void UMineralMineComponent::BindToInput()
{
	auto InputComp = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComp)
	{
		InputComp->BindAction("Mine", EInputEvent::IE_Pressed, this, &UMineralMineComponent::MineSwitch);
	}
}

void UMineralMineComponent::MineSwitch()
{
	if (bMining)
	{
		MineStop();
	}
	else
	{
		Mine();
	}
}


// Called every frame
void UMineralMineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Mining(DeltaTime);
}

