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
	
	return {Resource.Resource, Amount};
}

// Called when the game starts or when spawned
void AOre::BeginPlay()
{
	Super::BeginPlay();

	
}
