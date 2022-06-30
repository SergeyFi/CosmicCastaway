// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ore.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SleepInterface.h"
#include "Asteroid.generated.h"


USTRUCT(BlueprintType)
struct FOreInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AOre> OreClass;
	
	UPROPERTY(EditDefaultsOnly)
	int32 SpawnChance;
};

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

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
	float ScaleMin = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
	float ScaleMax = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
	int32 MaxOreCount = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
	TArray<FOreInfo> OresInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
	UStaticMeshComponent* AsteroidMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Asteroid")
	TArray<UStaticMesh*> AsteroidMeshes; 

private:

	FRotator RandomRotation;

	void SetChildCollision(bool bCollision);

	bool bIsSleep;

	void Randomize();

	void GenerateOre();

	TSubclassOf<AOre> GetRandomOreClass();

};
