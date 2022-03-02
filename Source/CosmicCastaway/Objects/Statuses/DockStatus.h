// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Statuses/StatusGetter.h"
#include "Components/Dock.h"
#include "DockStatus.generated.h"

/**
 * 
 */
UCLASS()
class COSMICCASTAWAY_API UDockStatus : public UStatusGetter
{
	GENERATED_BODY()

public:
	virtual void UpdateStatus() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Status")
	FText DockStatusMessage;

private:

	UDock* DockComponent;
};
