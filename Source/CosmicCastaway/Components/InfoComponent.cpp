// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InfoComponent.h"

// Sets default values for this component's properties
UInfoComponent::UInfoComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FInfoData UInfoComponent::GetInfoData()
{
	return Info;
}


// Called when the game starts
void UInfoComponent::BeginPlay()
{
	Super::BeginPlay();

	Info.FullName = "";

	Info.FullName.Append(Info.FirstName.ToString());
	Info.FullName.Append("-");
	Info.FullName.Append(FString::FromInt(FMath::RandRange(1, 99)));
	Info.FullName.Append(Prefixes[FMath::RandRange(0, Prefixes.Num() - 1)]);

}
