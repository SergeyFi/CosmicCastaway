// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Widgets/TargetWidget.h"

void UTargetWidget::SetOwner(AActor* Owner)
{
	WidgetOwner = Owner;
}

FString UTargetWidget::GetFullName()
{
	FString FullName;
	FullName.Append(TargetName.ToString());
	FullName.Append("-");
	FullName.Append(FString::FromInt(FMath::RandRange(1, 99)));
	FullName.Append(Prefixes[FMath::RandRange(0, Prefixes.Num() - 1)]);
	
	return FullName;
}
