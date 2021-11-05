// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipOrientationComponent.h"

// Sets default values for this component's properties
UShipOrientationComponent::UShipOrientationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetTickGroup(ETickingGroup::TG_PrePhysics);
}


// Called when the game starts
void UShipOrientationComponent::BeginPlay()
{
	Super::BeginPlay();

	BindToInput();
}

void UShipOrientationComponent::BindToInput()
{
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();

	InputComp->BindAxis("MoveRight");
	InputComp->BindAxis("MoveUp");
}

void UShipOrientationComponent::UpdateRotation(float DeltaTime)
{
	FRotator RotatorResult;
	RotatorResult.Yaw = (MoveRightScale * InputComp->GetAxisValue("MoveRight")) * DeltaTime;
	RotatorResult.Pitch = (MoveUpScale * InputComp->GetAxisValue("MoveUp")) * DeltaTime;

	GetOwner()->AddActorLocalRotation(RotatorResult);
}

// Called every frame
void UShipOrientationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateRotation(DeltaTime);
}

