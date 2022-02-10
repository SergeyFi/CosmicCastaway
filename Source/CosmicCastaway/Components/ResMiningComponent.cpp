// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ResMiningComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actors/Ore.h"

// Sets default values for this component's properties
UResMiningComponent::UResMiningComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UResMiningComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetComponentTickEnabled(false);

	DockComponent = GetOwner()->FindComponentByClass<UDock>();

#if WITH_EDITOR
	if (!DockComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Blue,
			TEXT("Need DockComponent for resource mining"));
	}
#endif
	

	ResourcesStorage = GetOwner()->FindComponentByClass<UResourcesStorage>();

#if WITH_EDITOR
	if (!ResourcesStorage)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Blue,
			TEXT("Need ResourcesStorage for resource mining"));
	}
#endif

	if (ResourcesStorage && DockComponent)
	{
		BindToInput();
	}
	
}

void UResMiningComponent::BindToInput()
{
	auto InputComp = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComp)
	{
		InputComp->BindAction("Mine", EInputEvent::IE_Pressed, this, &UResMiningComponent::MineSwitch);
	}
}

void UResMiningComponent::MineSwitch()
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

void UResMiningComponent::MineStop()
{
	bMining = false;
	SetComponentTickEnabled(false);

#if WITH_EDITOR
	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Blue, TEXT("Mine stop"));
	}
#endif
}

void UResMiningComponent::Mine()
{
	bMining = true;
	SetComponentTickEnabled(true);

#if WITH_EDITOR
  	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Blue, TEXT("Mine start"));
	}
#endif
}

void UResMiningComponent::UpdateMining()
{
	MineInfo = MiningModule->GetDefaultObject<UMiningModule>()->GetMineInfo();
	
	PrimaryComponentTick.TickInterval = MineInfo.MineRate;
}

void UResMiningComponent::Mining(float DeltaTime)
{
	if (!DockComponent || !DockComponent->IsDock())
	{
		MineStop();
		return;
	}

	TArray<FHitResult> HitResults;

	auto DebugDraw = EDrawDebugTrace::None;

#if WITH_EDITOR
	if (bDebug)
	{
		DebugDraw = EDrawDebugTrace::ForOneFrame;
	}
#endif
	

	auto bHit = UKismetSystemLibrary::SphereTraceMulti
	(
	GetOwner(),
	GetComponentLocation(),
	GetComponentLocation() + GetForwardVector() * MineInfo.MineDistance,
	MineInfo.MineRadius,
	TraceType,
	false,
	{GetOwner()},
	DebugDraw,
	HitResults,
	true
	);

	if (bHit)
	{
		AOre* OreNearest = nullptr;
		
		for (const auto& Hit : HitResults)
		{
			auto Ore = Cast<AOre>(Hit.GetActor());

			if (Ore)
			{
				if (OreNearest)
				{
					if (Ore->GetDistanceTo(GetOwner()) < OreNearest->GetDistanceTo(GetOwner()))
					{
						OreNearest = Ore;
					}
				}
				else
				{
					OreNearest = Ore;
				}
			}
		}

		if (OreNearest)
		{
			ResourcesStorage->AddResourceByValue(OreNearest->MineResource(MineInfo.MinePerSecond * DeltaTime));
		}
		else
		{
			MineStop();
		}
	}
	
}


// Called every frame
void UResMiningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Mining(DeltaTime);
}

void UResMiningComponent::SetMiningModule(TSubclassOf<UMiningModule> Module)
{
	if (Module)
	{
		MiningModule = Module;
	}
}

