// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipElements/EngineElement.h"
#include "Components/RocketEngine.h"

void UEngineElement::BeginPlay()
{
	Super::BeginPlay();

	if (EngineModule)
	{
		auto RocketEngine = GetOwner()->FindComponentByClass<URocketEngine>();

		if (RocketEngine)
		{
			RocketEngine->SetEngineModule(EngineModule);
		}
	}
}
