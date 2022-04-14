// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointInterest.generated.h"

UCLASS()
class COSMICCASTAWAY_API APointInterest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointInterest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
