// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStatusComponent::AddStatus(TSubclassOf<UStatus> Status)
{
	Statuses.Add(Status);

	OnUpdated.Broadcast();
}

void UStatusComponent::RemoveStatus(TSubclassOf<UStatus> Status)
{
	Statuses.Remove(Status);

	OnUpdated.Broadcast();
}

void UStatusComponent::UpdateStatus(TSubclassOf<UStatus> Status, FText StatusText)
{
	Status->GetDefaultObject<UStatus>()->Status = StatusText;
}

FText UStatusComponent::GetStatusText(TSubclassOf<UStatus> Status)
{
	return Status->GetDefaultObject<UStatus>()->Status;
}

bool UStatusComponent::StatusIsActive(TSubclassOf<UStatus> Status)
{
	return Statuses.Contains(Status);
}

 void UStatusComponent::GetPublicStatuses(TArray<TSubclassOf<UStatus>>& PublicStatuses)
{
	for (auto& Status : Statuses)
	{
		if (!Status->GetDefaultObject<UStatus>()->bInternal)
		{
			PublicStatuses.Add(Status);
		}
	}
}
