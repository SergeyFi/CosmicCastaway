// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SleepInterface.h"
#include "Asteroid.generated.h"

UCLASS()
class COSMICCASTAWAY_API AAsteroid : public AActor, public ISleepInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Sleep() override;

	virtual void WakeUp() override;

	virtual bool IsSleep() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
	float RotationSpeed = 0.01f;

private:

	FRotator RandomRotation;

	void SetChildCollision(bool bCollision);

	bool bIsSleep;

};
