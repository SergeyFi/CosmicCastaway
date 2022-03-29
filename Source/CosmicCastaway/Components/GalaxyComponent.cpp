// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GalaxyComponent.h"

#include "Engine/AssetManager.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/WorldComposition.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGalaxyComponent::UGalaxyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGalaxyComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialLevel.LoadSynchronous();
	
	NewLevel({0.0f, 0.0f, 0.0f}, InitialLevel);
	
}

void UGalaxyComponent::CheckPlayerPosition()
{
	auto Position = GetOwner()->GetActorLocation();

	auto Xabs = std::abs(Position.X);
	auto Xsign = FMath::Sign(Position.X);
	auto Yabs = std::abs(Position.Y);
	auto Zabs = std::abs(Position.Z);

	if (Xabs > Bound || Yabs > Bound || Zabs > Bound)
	{
		GetWorld()->RequestNewWorldOrigin(FIntVector{GetOwner()->GetActorLocation()} + GetWorld()->OriginLocation);
	}

	if (Xabs > Bound && Xsign > 0.0f)
	{
		NewLevel({1.0f, 0.0f, 0.0f}, InitialLevel);

		if (Chance())
		{
			NewLevel({1.0f, 1.0f, 0.0f}, InitialLevel);
		}

		if (Chance())
		{
			NewLevel({1.0f, -1.0f, 0.0f}, InitialLevel);
		}
	}
}

void UGalaxyComponent::NewLevel(FVector Direction, TSoftObjectPtr<UWorld>& Level)
{
	if (Level)
	{
		auto WorldOffset = GetWorld()->OriginLocation;
		
		FVector Location;
		Location.X = WorldOffset.X;
		Location.X += (Bound * 2.0f) * Direction.X;
		Location.Y = WorldOffset.Y;
		Location.Y += (Bound * 2.0f) * Direction.Y;
		

		bool Succsess = false;
		CurrentLevel = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr
		(GetOwner(), Level, Location, {0.0f, 0.0f, 0.0f}, Succsess);
	}
}

bool UGalaxyComponent::Chance()
{
	auto Chance = FMath::RandRange(0.0f, 1.0f);

	if (Chance > BrunchChance)
	{
		return true;
	}

	return false;
}

// Called every frame
void UGalaxyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckPlayerPosition();
}

