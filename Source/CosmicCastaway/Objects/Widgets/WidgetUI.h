// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Objects/WidgetTypes/WidgetType.h"
#include "WidgetUI.generated.h"

/**
 * 
 */
UCLASS()
class COSMICCASTAWAY_API UWidgetUI : public UUserWidget
{
	GENERATED_BODY()

public:

	TSubclassOf<UWidgetType> GetWidgetType();

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWidgetType> WidgetType = UWidgetType::StaticClass();
};
