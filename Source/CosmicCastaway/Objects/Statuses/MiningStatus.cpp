// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Statuses/MiningStatus.h"

void UMiningStatus::UpdateStatus()
{
	Super::UpdateStatus();

	if (ResMining)
	{
		if (ResMining->IsMining())
		{
			auto MiningOre = ResMining->GetCurrentMiningOre();
			if (MiningOre)
			{
				 auto Message =
				FText::Join(FText::FromString(""), MiningStatusMessage, FText::FromString(" "),
				FText::FromString(FString::FromInt(MiningOre->GetResourcesCountInPercent() * 100.0f)), FText::FromString("%"));
				
				Status.Status = Message;
				Status.bActive = true;
			}
		}
		else
		{
			Status.bActive = false;
		}
	}
	else
	{
		ResMining = Cast<AActor>(GetOuter())->FindComponentByClass<UResMiningComponent>();
	}
}
