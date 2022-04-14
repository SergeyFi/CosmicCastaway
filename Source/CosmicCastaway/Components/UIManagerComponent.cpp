// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UIManagerComponent.h"

// Sets default values for this component's properties
UUIManagerComponent::UUIManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUIManagerComponent::SetWidgetVisibility(TSubclassOf<UWidgetUI> WidgetClass, ESlateVisibility Visibility)
{
	auto Widget = GetWidgetByClass(WidgetClass);
	
	if (Widget)
	{
		Widget->SetVisibility(Visibility);
	}
}

UWidgetUI* UUIManagerComponent::GetWidgetByClass(TSubclassOf<UWidgetUI> WidgetClass)
{
	for (const auto& Widget : Widgets)
	{
		if (Widget->GetClass() == WidgetClass)
		{
			return Widget;
		}
	}
	
	return nullptr;
}

void UUIManagerComponent::SetVisibilityByType(TSubclassOf<UWidgetType> Type, ESlateVisibility Visibility)
{
	for (const auto& Widget : Widgets)
	{
		if (Widget->GetWidgetType() == Type)
		{
			Widget->SetVisibility(Visibility);
		}
	}
}

void UUIManagerComponent::HideAll()
{
	for (const auto& Widget : Widgets)
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
}


// Called when the game starts
void UUIManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	Update3DWidgets();
}

void UUIManagerComponent::Update3DWidgets()
{
	TArray<UWidgetComponent*> OwnerWidgetComponents;

	GetOwner()->GetComponents(OwnerWidgetComponents);
	
	for (const auto Widget3D : OwnerWidgetComponents)
	{
		auto WidgetUI = Cast<UWidgetUI>(Widget3D->GetWidget());

		if (WidgetUI)
		{
			Widgets.Add(WidgetUI);
		}
	}
}
