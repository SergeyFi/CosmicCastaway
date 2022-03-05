// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipElements/MiningElement.h"

#include "Components/ResMiningComponent.h"

void UMiningElement::BeginPlay()
{
	Super::BeginPlay();

	auto MiningComponent = GetOwner()->FindComponentByClass<UResMiningComponent>();

	if (MiningComponent)
	{
		FString Message;
		
		MiningComponent->SetMiningData(DataTable->FindRow<FMiningData>(DataID, Message));
	}
}
