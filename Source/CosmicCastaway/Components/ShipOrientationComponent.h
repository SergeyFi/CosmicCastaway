// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShipOrientationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UShipOrientationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShipOrientationComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Orientation")
	void BlockOrientation();

	UFUNCTION(BlueprintCallable, Category = "Orientation")
	void UnBlockOrientation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Orientation")
	float MoveRightScale = 25.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Orientation")
	float MoveUpScale = 25.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Orientation")
	float RotationInterpSpeed = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Orientation")
	float InputScale = 4.0f;

private:

	void BindToInput();

	UInputComponent* InputComp;

	void UpdateRotation(float DeltaTime);

	FRotator RotationInterp;
};
