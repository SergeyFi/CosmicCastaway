// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Ore.h"

// Sets default values
AOre::AOre()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OreMesh = CreateDefaultSubobject<UStaticMeshComponent>("OreMesh");
	RootComponent = OreMesh;

}

FResourceValue AOre::MineResource(float Value)
{
	if (Resource.Value <= 0.0f)
	{
		DestroyOre();
		return {Resource.Resource, 0.0f};
	}
	
	float Amount = Value;
	
	if (Resource.Value < Value)
	{
		Amount = Resource.Value;
	}

	Resource.Value -= Amount;

	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue("Dissolve",1.0f - Resource.Value / InitialResValue);
	}
	else
	{
		auto MeshComponent = FindComponentByClass<UStaticMeshComponent>();
		DynamicMaterial = MeshComponent->CreateDynamicMaterialInstance(0, MeshComponent->GetMaterial(0));
	}
	
	return {Resource.Resource, Amount};
}

// Called when the game starts or when spawned
void AOre::BeginPlay()
{
	Super::BeginPlay();

	RandomRangeScale();

	InitialResValue = Resource.Value;
}

void AOre::RandomRangeScale()
{
	auto Scale = FMath::RandRange(ScaleMin, ScaleMax);
	SetActorScale3D({Scale, Scale, Scale});

	AddActorLocalOffset({0.0f, 0.0f, ZOffset / Scale});
}
