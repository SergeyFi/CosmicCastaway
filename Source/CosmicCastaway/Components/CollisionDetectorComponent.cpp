// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CollisionDetectorComponent.h"

// Sets default values for this component's properties
UCollisionDetectorComponent::UCollisionDetectorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCollisionDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

float UCollisionDetectorComponent::GetCollisionDistance()
{
	EDrawDebugTrace::Type DebugType = EDrawDebugTrace::None;

#if WITH_EDITOR
	if (bDebug)
	{
		DebugType = EDrawDebugTrace::ForOneFrame;
	}
#endif

	FHitResult HitResult;

	auto End = GetOwner()->GetVelocity();
	End.Normalize();
	End *= DetectorLength;
	End += GetOwner()->GetActorLocation();
	
	UKismetSystemLibrary::SphereTraceSingle
	(
		GetOwner(),
		GetOwner()->GetActorLocation(),
		End,
		DetectorRadius,
		CollisionType,
		false,
		{},
		DebugType,
		HitResult,
		true
	);

	CollisionLocation = HitResult.Location;

	return HitResult.Distance;
}


// Called every frame
void UCollisionDetectorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CollisionTime = GetCollisionDistance() / GetOwner()->GetVelocity().Size();
}

float UCollisionDetectorComponent::GetCollisionTime()
{
	return CollisionTime;
}

FVector UCollisionDetectorComponent::GetCollisionLocation()
{
	return CollisionLocation;
}

