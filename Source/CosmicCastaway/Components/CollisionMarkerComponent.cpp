// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CollisionMarkerComponent.h"

#include "Kismet/KismetMathLibrary.h"

UCollisionMarkerComponent::UCollisionMarkerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UCollisionMarkerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionDetector = GetOwner()->FindComponentByClass<UCollisionDetectorComponent>();

	if (!DefaultMaterial || !CollisionMaterial)
	{
		SetComponentTickEnabled(false);
	}
}

void UCollisionMarkerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
	if (!CollisionDetector->IsColliding() && GetOwner()->GetVelocity().IsNearlyZero(0.5f))
	{
		SetWorldLocation(GetOwner()->GetActorForwardVector() * Length + GetOwner()->GetActorLocation());

		SetWorldScale3D({1.0f, 1.0f, 1.0f});
		SetMaterial(0,DefaultMaterial);
	}
	else if (!CollisionDetector->IsColliding())
	{
		auto VelDirection = GetOwner()->GetVelocity();
		VelDirection.Normalize();
		
		SetWorldLocation(VelDirection * Length + GetOwner()->GetActorLocation());

		SetWorldScale3D({1.0f, 1.0f, 1.0f});
		SetMaterial(0,DefaultMaterial);
	}
	else
	{
		SetWorldLocation(CollisionDetector->GetCollisionLocation());

		SetMaterial(0, CollisionMaterial);
		
		auto Scale = UKismetMathLibrary::MapRangeClamped(
			CollisionDetector->GetDistanceCollision(),
			0.0f,
			CollisionDetector->GetDetectorLength(),
			0.05f, 2.0f);

		SetWorldScale3D({Scale, Scale, Scale});
	}
}
