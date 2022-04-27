// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipOrientationComponent.h"
#include "Components/StatusComponent.h"
#include "Objects/Statuses/StatusBusy.h"

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

	StatusComp = GetOwner()->FindComponentByClass<UStatusComponent>();
}

void UShipOrientationComponent::BindToInput()
{
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();

	InputComp->BindAxis("MoveRight");
	InputComp->BindAxis("MoveUp");
	InputComp->BindAxis("RotationZ");
}

void UShipOrientationComponent::UpdateRotation(float DeltaTime)
{
	FRotator RotatorResult;

	RotatorResult.Yaw = MoveRightScale * InputComp->GetAxisValue("MoveRight");
	RotatorResult.Pitch = MoveUpScale * InputComp->GetAxisValue("MoveUp");
	RotatorResult.Roll = MoveUpScale * InputComp->GetAxisValue("RotationZ");

	RotatorResult *= InputScale;

	if (StatusComp->StatusIsActive(UStatusBusy::StaticClass()))
	{
		RotatorResult = FRotator{};
	}

	RotationInterp = FMath::RInterpTo(RotationInterp, RotatorResult, DeltaTime, RotationInterpSpeed);
	
	GetOwner()->AddActorLocalRotation(RotationInterp * DeltaTime);
}

// Called every frame
void UShipOrientationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateRotation(DeltaTime);
}

void UShipOrientationComponent::BlockOrientation()
{
	SetComponentTickEnabled(false);
}

void UShipOrientationComponent::UnBlockOrientation()
{
	SetComponentTickEnabled(true);
}

