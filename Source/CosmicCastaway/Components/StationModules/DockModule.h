// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/DockInterface.h"
#include "DockModule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDockDelegate, APawn*, Docker);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UDockModule : public UStaticMeshComponent, public IDockInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDockModule();

	virtual void Dock(APawn* Docker) override;

	virtual void UnDock(APawn* Docker) override;

	UPROPERTY(BlueprintAssignable, Category = "Dock")
	FDockDelegate OnDock;

	UPROPERTY(BlueprintAssignable, Category = "Dock")
	FDockDelegate OnUnDock;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
