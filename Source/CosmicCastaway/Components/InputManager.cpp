// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputManager.h"

// Sets default values for this component's properties
UInputManager::UInputManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


float UInputManager::GetUpDownValue()
{
	return 0.0f;
}

float UInputManager::GetLeftRightValue()
{
	return 0.0f;
}

// Called when the game starts
void UInputManager::BeginPlay()
{
	Super::BeginPlay();

	FindAndBindToInputComp();
}

void UInputManager::OnMoveUp(float Value)
{
	EventUpDown.Broadcast(Value);
}

void UInputManager::OnMoveRight(float Value)
{
	EventLeftRight.Broadcast(Value);
}

void UInputManager::FindAndBindToInputComp()
{
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();

	InputComp->BindAxis("MoveUp", this, &UInputManager::OnMoveUp);

	InputComp->BindAxis("MoveRight", this, &UInputManager::OnMoveRight);
}
