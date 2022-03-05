// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipElements/EngineElement.h"
#include "Components/RocketEngine.h"

void UEngineElement::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable)
	{
		auto RocketEngine = GetOwner()->FindComponentByClass<URocketEngine>();

		if (RocketEngine)
		{
			FString Message;
			auto DataPtr = DataTable->FindRow<FEngineData>(DataID, Message);

			if (DataPtr)
			{
				RocketEngine->SetEngineData(DataTable->FindRow<FEngineData>(DataID, Message));
			}
		}
	}
}
