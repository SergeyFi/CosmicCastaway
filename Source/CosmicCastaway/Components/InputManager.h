// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAxisInput, float, Value);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UInputManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputManager();

	UPROPERTY(BlueprintAssignable, Category = "InputManager")
	FAxisInput EventUpDown;

	UPROPERTY(BlueprintAssignable, Category = "InputManager")
	FAxisInput EventLeftRight;

	UFUNCTION(BlueprintPure,  Category = "InputManager")
	float GetUpDownValue();

	UFUNCTION(BlueprintPure,  Category = "InputManager")
	float GetLeftRightValue();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnMoveUp(float Value);

	UFUNCTION()
	void OnMoveRight(float Value);

private:

	UInputComponent* InputComp;

	void FindAndBindToInputComp();
};
