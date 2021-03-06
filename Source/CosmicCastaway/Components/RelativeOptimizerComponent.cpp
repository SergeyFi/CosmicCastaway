// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RelativeOptimizerComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
URelativeOptimizerComponent::URelativeOptimizerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = UpdateTime;
}


// Called when the game starts
void URelativeOptimizerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void URelativeOptimizerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UGameplayStatics::GetAllActorsWithInterface(this, USleepInterface::StaticClass(), Sleepers);

	for (auto Actor : Sleepers)
	{
		auto Sleeper = Cast<ISleepInterface>(Actor);
		
		if (FVector::Distance(Actor->GetActorLocation(), GetOwner()->GetActorLocation()) < Distance)
		{
			if (Sleeper->IsSleep())
			{
				Sleeper->WakeUp();
			}
		}
		else
		{
			if (!Sleeper->IsSleep())
			{
				Sleeper->Sleep();
			}
		}
	}
}

