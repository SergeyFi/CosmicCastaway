// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Statuses/DockStatus.h"

void UDockStatus::UpdateStatus()
{
	Super::UpdateStatus();

	if (DockComponent)
	{
		if (DockComponent->IsDock())
		{
			Status.Status = DockStatusMessage;
			Status.bActive = true;
		}
		else
		{
			Status.bActive = false;
		}
	}
	else
	{
		DockComponent = Cast<AActor>(GetOuter())->FindComponentByClass<UDock>();
	}
}
