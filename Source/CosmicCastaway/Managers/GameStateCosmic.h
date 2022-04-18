// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/System.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateCosmic.generated.h"

/**
 * 
 */
UCLASS()
class COSMICCASTAWAY_API AGameStateCosmic : public AGameStateBase
{
	GENERATED_BODY()

public:
	void AddSystem(ASystem* System);

	void RemoveSystem(ASystem* System);

	UFUNCTION(BlueprintPure, Category = "Systems")
	TArray<ASystem*>& GetSystems();

private:

	TArray<ASystem*> Systems;
};
