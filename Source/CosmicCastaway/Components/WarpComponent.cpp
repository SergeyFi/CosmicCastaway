// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WarpComponent.h"

// Sets default values for this component's properties
UWarpComponent::UWarpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWarpComponent::Warp(AActor* NewTarget)
{
	if (!bWarping)
	{
		bWarping = true;

		Target = NewTarget;
		WarpTargetDirection = Target->GetActorLocation();
		WarpTargetDirection.Normalize();
		
		SetComponentTickEnabled(true);
	}
}

bool UWarpComponent::IsWarping()
{
	return bWarping;
}

void UWarpComponent::StopWarping()
{
	if (bWarping)
	{
		bWarping = false;
		SetComponentTickEnabled(false);
	}
}

void UWarpComponent::Warping(float DeltaTime)
{
	float CurrentWarpDistance = GetOwner()->GetDistanceTo(Target);

	if (CurrentWarpDistance < WarpStopDistance)
	{
		OwnerRoot->AddForce(-GetOwner()->GetVelocity() * WarpStopForce);

		if (GetOwner()->GetVelocity().Size() < WarpStopSpeed)
		{
			StopWarping();
		}
		
		return;
	}
	
	if (GetOwner()->GetVelocity().Size() < WarpMaxSpeed)
	{
		OwnerRoot->AddForce
		(WarpTargetDirection * WarpEnergyCoefficient * WarpEnergy);
	}
}

// Called when the game starts
void UWarpComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);

	OwnerRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}


// Called every frame
void UWarpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Warping(DeltaTime);
}

