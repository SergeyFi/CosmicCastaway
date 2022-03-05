// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Data/ElementsDataTables.h"
#include "ShipElement.generated.h"

/**
 * 
 */
UCLASS()
class COSMICCASTAWAY_API UShipElement : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Element")
	FName DataID;
	
	UPROPERTY(EditDefaultsOnly, Category = "Element")
	UDataTable* DataTable;
};
