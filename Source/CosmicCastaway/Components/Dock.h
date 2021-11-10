// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RocketEngine.h"
#include "ShipOrientationComponent.h"
#include "Components/ActorComponent.h"
#include "Dock.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UDock : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDock();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Dock")
	float GetCollisionDistance();

	UFUNCTION(BlueprintPure, Category = "Dock")
	bool IsDock();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Dock")
	float DockDistance = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Dock")
	float TraceDistance = 2000.0f;

private:

	void Dock();

	void UnDock();

	void DockSwitching();

	void BindToInput();

	void CollisionDetection();

	void FindOwnerPhysxComponent();

	void FindEngine();

	void FindOrientationComp();

	void Reset();

	bool bDock;

	float CollisionDistance;

	AActor* DockActor;

	UPrimitiveComponent* PhysxComponent;

	UPrimitiveComponent* DockComponent;

	URocketEngine* RocketEngine;

	UShipOrientationComponent* OrientationComp;
};
