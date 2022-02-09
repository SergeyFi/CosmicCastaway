// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/Resources/Resource.h"
#include "Ore.generated.h"



UCLASS(Blueprintable)
class COSMICCASTAWAY_API AOre : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOre();

	UFUNCTION(BlueprintCallable, Category = "Ore")
	TArray<FResourceValue>& GetResources();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Ore")
	TArray<FResourceValue> Resources;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ore")
	UStaticMeshComponent* OreMesh;
};