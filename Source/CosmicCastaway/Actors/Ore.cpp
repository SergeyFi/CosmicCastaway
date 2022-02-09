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

TArray<FResourceValue>& AOre::GetResources()
{
	return Resources;
}

// Called when the game starts or when spawned
void AOre::BeginPlay()
{
	Super::BeginPlay();
	
}
