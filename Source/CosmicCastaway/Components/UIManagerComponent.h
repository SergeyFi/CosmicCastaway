// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "Objects/Widgets/WidgetUI.h"
#include "UIManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UUIManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUIManagerComponent();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetWidgetVisibility(TSubclassOf<UWidgetUI> WidgetClass, ESlateVisibility Visibility);
	
	UFUNCTION(BlueprintPure, Category = "UI")
	UWidgetUI* GetWidgetByClass(TSubclassOf<UWidgetUI> WidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetVisibilityByType(TSubclassOf<UWidgetType> Type, ESlateVisibility Visibility);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideAll();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	void Update3DWidgets();

	TArray<UWidgetUI*> Widgets;
};
