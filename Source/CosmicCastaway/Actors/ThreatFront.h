// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ThreatFront.generated.h"

UCLASS()
class COSMICCASTAWAY_API AThreatFront : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThreatFront();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ThreatFront")
	float Speed = 1000.0f;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxDetector;

	
};
