// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DockInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDockInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COSMICCASTAWAY_API IDockInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Dock(APawn* Docker);

	virtual void UnDock(APawn* Docker);
};
