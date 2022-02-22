// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ShipElements/ShipElement.h"
#include "ShipBuilderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UShipBuilderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShipBuilderComponent();

	UFUNCTION(BlueprintCallable, Category = "ShipBuild")
	void Build();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "ShipBuild")
	TArray<TSubclassOf<UShipElement>> ShipBuild;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ShipBuild")
	TArray<USceneComponent*> CurrentBuild;

	UPROPERTY(EditDefaultsOnly, Category = "ShipBuild")
	FName SocketConnectorName = "Separator";

private:

	UPROPERTY()
	UStaticMeshComponent* PrevElement;
};
