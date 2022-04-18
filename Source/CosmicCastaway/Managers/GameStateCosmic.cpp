// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/GameStateCosmic.h"

void AGameStateCosmic::AddSystem(ASystem* System)
{
	Systems.Add(System);
}

void AGameStateCosmic::RemoveSystem(ASystem* System)
{
	Systems.Remove(System);
}

TArray<ASystem*>& AGameStateCosmic::GetSystems()
{
	return Systems;
}
