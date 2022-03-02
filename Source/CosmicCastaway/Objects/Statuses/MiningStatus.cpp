// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Statuses/MiningStatus.h"

void UMiningStatus::UpdateStatus()
{
	Super::UpdateStatus();

	if (ResMining)
	{
		if (ResMining->IsMining())
		{
			Status.Status = MiningStatusMessage;
			Status.StatusVisibility = EStatusVisibility::Display;
		}
		else
		{
			Status.StatusVisibility = EStatusVisibility::Hide;
		}
	}
	else
	{
		ResMining = Cast<AActor>(GetOuter())->FindComponentByClass<UResMiningComponent>();
	}
}
