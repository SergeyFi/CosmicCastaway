// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class COSMICCASTAWAY_API UTargetWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetOwner(AActor* Owner);
	
protected:

	UPROPERTY(BlueprintReadOnly,  Category = "Target")
	AActor* WidgetOwner;
};