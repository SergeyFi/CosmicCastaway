// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CollisionDetectorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UCollisionDetectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollisionDetectorComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Collision")
	float GetCollisionTime();

	UFUNCTION(BlueprintPure, Category = "Collision")
	FVector GetCollisionLocation();

	UFUNCTION(BlueprintPure, Category = "Collision")
	float GetDetectorLength();

	UFUNCTION(BlueprintPure, Category = "Collision")
	bool IsColliding();

	UFUNCTION(BlueprintPure, Category = "Collision")
	float GetDistanceCollision();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	float DetectorLength;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	float DetectorRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	bool bDebug;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	TEnumAsByte<ETraceTypeQuery> CollisionType;
	

private:
	float GetCollisionDistance();

	float CollisionTime;

	FVector CollisionLocation;

	bool bColliding;

	float CollisionDistance;
		
};
