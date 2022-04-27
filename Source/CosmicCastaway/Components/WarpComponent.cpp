// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WarpComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UWarpComponent::UWarpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWarpComponent::Warp(AActor* NewTarget)
{
	if (!bWarping && NewTarget)
	{
		bWarping = true;

		Target = NewTarget;
		WarpTargetDirection = UKismetMathLibrary::FindLookAtRotation
		(GetOwner()->GetActorLocation(), Target->GetActorLocation()).Vector();
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

		Target = nullptr;
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

