// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RocketEngine.h"

// Sets default values for this component's properties
URocketEngine::URocketEngine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void URocketEngine::BeginPlay()
{
	Super::BeginPlay();

	GetOwnerRoot();

	BindToInput();

	FindFuelTank();
	
}

void URocketEngine::GetOwnerRoot()
{
	OwnerRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!OwnerRoot)
	{
		SetComponentTickEnabled(false);
	}
}

void URocketEngine::AddEngineForce(float DeltaTime)
{
	auto Force =
		GetOwner()->GetActorForwardVector() * DeltaTime * Coefficient * Thrust * InputComponent->GetAxisValue("EngineForward");

	OwnerRoot->AddForce(Force);

	FuelWaste(Force.Size() / Coefficient * DeltaTime * EngineThrustEfficiency);
}

void URocketEngine::BindToInput()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	InputComponent->BindAxis("EngineForward");

	InputComponent->BindAction("FullStop", EInputEvent::IE_Pressed, this, &URocketEngine::FullStopTrue);
	InputComponent->BindAction("FullStop", EInputEvent::IE_Released, this, &URocketEngine::FullStopFalse);
}

void URocketEngine::FullStopTrue()
{
	bFullStop = true;
}

void URocketEngine::FullStopFalse()
{
	bFullStop = false;
}


// Called every frame
void URocketEngine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AddEngineForce(DeltaTime);

	FullStop(DeltaTime);
}

void URocketEngine::StartEngine()
{
	SetComponentTickEnabled(true);
}

void URocketEngine::StopEngine()
{
	SetComponentTickEnabled(false);
}

void URocketEngine::FullStop(float DeltaTime)
{
	if (bFullStop)
	{
		auto OwnerVelocity = GetOwner()->GetVelocity();
		
		auto Force = OwnerVelocity * ThrustFullStop;

		if (OwnerVelocity.Size() < 300.0f)
		{
			Force *= 2.0f;
		}
		else if (OwnerVelocity.Size() < 100.0f)
		{
			Force *= 8.0f;
		}
		else if (OwnerVelocity.Size() < 50.0f)
		{
			Force *= 20.0f;
		}
		else if (OwnerVelocity.Size() < 25.0f)
		{
			Force *= 100.0f;
		}
		
		OwnerRoot->AddForce(-Force);

		FuelWaste(Force.Size() / Coefficient * DeltaTime * EngineFullStopEfficiency);
	}
}

void URocketEngine::FindFuelTank()
{
	FuelTank = GetOwner()->FindComponentByClass<UFuelTank>();
}

void URocketEngine::FuelWaste(float Amount)
{
	if (FuelTank)
	{
		if (FuelTank->GetCurrentFuel() == 0.0f)
		{
			StopEngine();
		}

		FuelTank->RemoveFuel(Amount);
	}
}

