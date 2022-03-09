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

	auto LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), GetComponentLocation());

	auto Direction = UKismetMathLibrary::NormalizedDeltaRotator(LookAtRot, GetOwner()->GetActorRotation());

	auto DirectionAngleSum = (FMath::Abs(Direction.Yaw) + FMath::Abs(Direction.Pitch)) / 2.0f;
	
	
	if (!CollisionDetector->IsColliding() && GetOwner()->GetVelocity().IsNearlyZero(0.5f))
	{
		SetWorldLocation(GetOwner()->GetActorForwardVector() * MaxLength + GetOwner()->GetActorLocation());

		SetWorldScale3D({1.0f, 1.0f, 1.0f});
		SetMaterial(0,DefaultMaterial);
	}
	else if (!CollisionDetector->IsColliding())
	{
		auto VelDirection = GetOwner()->GetVelocity();
		VelDirection.Normalize();

		auto Length = UKismetMathLibrary::MapRangeClamped
		(DirectionAngleSum, 0.0f, DirectionMaxAngle, MaxLength, 200.0f);
		
		SetWorldLocation(VelDirection * Length + GetOwner()->GetActorLocation());

		auto Scale = UKismetMathLibrary::MapRangeClamped(
		Length,
		0.0f,
		CollisionDetector->GetDetectorLength(),
		0.05f, 2.00f);

		SetWorldScale3D({Scale, Scale, Scale});
		SetMaterial(0,DefaultMaterial);
	}
	else
	{
		auto DirectionVector = UKismetMathLibrary::GetDirectionUnitVector
		(GetOwner()->GetActorLocation(), CollisionDetector->GetCollisionLocation());
		
		float CollisionLength = FVector::Distance(GetOwner()->GetActorLocation(), CollisionDetector->GetCollisionLocation());

		CollisionLength = UKismetMathLibrary::MapRangeClamped
		(DirectionAngleSum, 0.0f, CollisionMaxAngle, CollisionLength, 200.0f);
		
		SetWorldLocation(DirectionVector * CollisionLength + GetOwner()->GetActorLocation());

		SetMaterial(0, CollisionMaterial);
		
		auto Scale = UKismetMathLibrary::MapRangeClamped(
			CollisionLength,
			0.0f,
			CollisionDetector->GetDetectorLength(),
			0.05f, 4.0f);

		SetWorldScale3D({Scale, Scale, Scale});
	}
}
