// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ResMiningComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "StatusComponent.h"
#include "Actors/Ore.h"
#include "Objects/Statuses/StatusMining.h"
#include "Objects/Statuses/StatusBusy.h"

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

	StatusComp = GetOwner()->FindComponentByClass<UStatusComponent>();

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
	StatusComp->RemoveStatus(UStatusMining::StaticClass());
	StatusComp->RemoveStatus(UStatusBusy::StaticClass());
	SetComponentTickEnabled(false);
	DockComponent->UnDock();

	StopNiagara();

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
	StatusComp->AddStatus(UStatusMining::StaticClass());
	StatusComp->AddStatus(UStatusBusy::StaticClass());
	SetComponentTickEnabled(true);

	StartNiagara();

#if WITH_EDITOR
  	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Blue, TEXT("Mine start"));
	}
#endif
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
	GetComponentLocation() + GetForwardVector() * MiningData.MineDistance,
	MiningData.MineRadius,
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
			ResourcesStorage->AddResourceByValue(OreNearest->MineResource(MiningData.MinePerSecond * DeltaTime));
			OreCurrent = OreNearest;
		}
		else
		{
			MineStop();
			OreCurrent = nullptr;
		}
	}
	
}

void UResMiningComponent::InitNiagara()
{
	if (!NiagaraComponent)
	{
		NiagaraComponent = NewObject<UNiagaraComponent>(GetOwner());
		NiagaraComponent->RegisterComponent();
		NiagaraComponent->SetWorldLocation(GetComponentLocation());
		NiagaraComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		NiagaraComponent->SetWorldScale3D({FXScale, FXScale, FXScale});
	}

	NiagaraComponent->SetAsset(MiningData.NiagaraFX);
	NiagaraComponent->DeactivateImmediate();
	
}

void UResMiningComponent::StartNiagara()
{
	NiagaraComponent->Activate();
}

void UResMiningComponent::StopNiagara()
{
	NiagaraComponent->Deactivate();
}

void UResMiningComponent::UpdateStatus()
{
	auto MiningOre = GetCurrentMiningOre();
	
	if (IsMining() && MiningOre)
	{
		auto Message =
	   FText::Join(FText::FromString(""), MiningStatusName, FText::FromString(" "),
	   FText::FromString(FString::FromInt(MiningOre->GetResourcesCountInPercent() * 100.0f)), FText::FromString("%"));
				
		StatusComp->UpdateStatus(UStatusMining::StaticClass(), Message);
	}
}


// Called every frame
void UResMiningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Mining(DeltaTime);

	UpdateStatus();
}

bool UResMiningComponent::IsMining()
{
	return bMining;
}

void UResMiningComponent::SetMiningData(FMiningData* Data)
{
	MiningData = *Data;
	InitNiagara();
}

AOre* UResMiningComponent::GetCurrentMiningOre()
{
	return OreCurrent;
}

