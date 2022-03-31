// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TargetComponent.h"
#include "Objects/Widgets/TargetWidget.h"

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	auto TargetWidget = Cast<UTargetWidget>(GetWidget());

	if (TargetWidget)
	{
		TargetWidget->SetOwner(GetOwner());
	}
}
