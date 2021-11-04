// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Dock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UDock::UDock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDock::BeginPlay()
{
	Super::BeginPlay();

	BindToInput();

	FindOwnerPhysxComponent();

	FindEngine();
}

void UDock::Dock()
{

	if (CollisionDistance <= DockDistance && DockActor && PhysxComponent && RocketEngine)
	{
		bDock = true;

		RocketEngine->StopEngine();
		PhysxComponent->SetSimulatePhysics(false);
		
		GetOwner()->AttachToActor
		(DockActor,
		{
			EAttachmentRule::KeepWorld,
			EAttachmentRule::KeepWorld,
				EAttachmentRule::KeepWorld,
			false}
		);

		TurnOffControllerRotation();
	}
}

void UDock::UnDock()
{
	
	GetOwner()->DetachFromActor({EDetachmentRule::KeepWorld, false});
	PhysxComponent->SetSimulatePhysics(true);
	RocketEngine->StartEngine();
	TurnOnControllerRotation();
	bDock = false;
}

void UDock::DockSwitching()
{
	if (bDock)
	{
		UnDock();
	}
	else
	{
		Dock();
	}
}

void UDock::BindToInput()
{
	auto InputComp = GetOwner()->FindComponentByClass<UInputComponent>();

	InputComp->BindAction("Docking", EInputEvent::IE_Pressed, this, &UDock::DockSwitching);
}

void UDock::CollisionDetection()
{
	FHitResult HitResult;
	
	bool bHit = UKismetSystemLibrary::LineTraceSingle
	(
		this,
		GetOwner()->GetActorLocation(),
		GetOwner()->GetActorForwardVector() * TraceDistance + GetOwner()->GetActorLocation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		{GetOwner()},
		EDrawDebugTrace::None,
		HitResult,
		true
	);

	if (bHit)
	{
		CollisionDistance = HitResult.Distance;
		DockActor = HitResult.Actor.Get();
		ImpactPoint = HitResult.ImpactPoint;
	}
	else
	{
		if (!bDock)
		{
			CollisionDistance = 0.0f;
			DockActor = nullptr;
		}
	}
}

void UDock::FindOwnerPhysxComponent()
{
	PhysxComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}

void UDock::FindEngine()
{
	RocketEngine = GetOwner()->FindComponentByClass<URocketEngine>();
}

void UDock::TurnOnControllerRotation()
{
	auto OwnerPawn = GetOwner<APawn>();
	
	OwnerPawn->GetController()->SetControlRotation(OwnerPawn->GetActorRotation());
	OwnerPawn->bUseControllerRotationPitch = true;
	OwnerPawn->bUseControllerRotationRoll = true;
	OwnerPawn->bUseControllerRotationYaw = true;
}

void UDock::TurnOffControllerRotation()
{
	auto OwnerPawn = GetOwner<APawn>();

	OwnerPawn->bUseControllerRotationPitch = false;
	OwnerPawn->bUseControllerRotationRoll = false;
	OwnerPawn->bUseControllerRotationYaw = false;
}

// Called every frame
void UDock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CollisionDetection();
}

float UDock::GetCollisionDistance()
{
	return CollisionDistance;
}

