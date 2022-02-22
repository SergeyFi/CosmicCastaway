// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipElements/MiningElement.h"

#include "Components/ResMiningComponent.h"

void UMiningElement::BeginPlay()
{
	Super::BeginPlay();

	if (MiningModule)
	{
		auto MiningComponent = GetOwner()->FindComponentByClass<UResMiningComponent>();

		if (MiningComponent)
		{
			MiningComponent->SetMiningModule(MiningModule);
		}
	}
}
