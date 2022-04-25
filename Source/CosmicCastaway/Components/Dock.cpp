// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Dock.h"
#include "Interfaces/DockInterface.h"
#include "StatusComponent.h"
#include "Objects/Statuses/StatusDock.h"
#include "Kismet/KismetSystemLibrary.h"

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

	FindStatusComponent();

	BindToInput();

	FindOwnerPhysxComponent();

	FindEngine();

	FindOrientationComp();
}

void UDock::FindStatusComponent()
{
	StatusComp = GetOwner()->FindComponentByClass<UStatusComponent>();
}

void UDock::Dock()
{

	if (CollisionDistance <= DockDistance && DockActor && PhysxComponent && RocketEngine)
	{
		bDock = true;

		RocketEngine->StopEngine();
		PhysxComponent->SetSimulatePhysics(false);
		OrientationComp->BlockOrientation();
		StatusComp->AddStatus(UStatusDock::StaticClass());
		
		GetOwner()->AttachToActor
		(DockActor,
		{
			EAttachmentRule::KeepWorld,
			EAttachmentRule::KeepWorld,
				EAttachmentRule::KeepWorld,
			false}
		);

		auto IDockComponent = Cast<IDockInterface>(DockComponent);

		if (IDockComponent)
		{
			IDockComponent->Dock(GetOwner<APawn>());
		}
	}
}

void UDock::UnDock()
{
	auto IDockComponent = Cast<IDockInterface>(DockComponent);

	if (IDockComponent)
	{
		IDockComponent->UnDock(GetOwner<APawn>());
	}
	
	GetOwner()->DetachFromActor({EDetachmentRule::KeepWorld, false});
	PhysxComponent->SetSimulatePhysics(true);
	RocketEngine->StartEngine();
	OrientationComp->UnBlockOrientation();
	StatusComp->RemoveStatus(UStatusDock::StaticClass());
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
		DockComponent = HitResult.GetComponent();
	}
	else
	{
		if (!bDock)
		{
			Reset();
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

void UDock::FindOrientationComp()
{
	OrientationComp = GetOwner()->FindComponentByClass<UShipOrientationComponent>();
}

void UDock::Reset()
{
	CollisionDistance = 0.0f;
	DockActor = nullptr;
	DockComponent = nullptr;
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

bool UDock::IsDock()
{
	return bDock;
}

