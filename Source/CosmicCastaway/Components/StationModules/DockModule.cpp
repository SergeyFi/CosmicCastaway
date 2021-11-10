// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StationModules/DockModule.h"

// Sets default values for this component's properties
UDockModule::UDockModule()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDockModule::Dock(APawn* Docker)
{
	OnDock.Broadcast(Docker);
}

void UDockModule::UnDock(APawn* Docker)
{
	OnUnDock.Broadcast(Docker);
}


// Called when the game starts
void UDockModule::BeginPlay()
{
	Super::BeginPlay();
	
}
