// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InfoComponent.generated.h"

USTRUCT(BlueprintType)
struct FInfoData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString FullName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName FirstName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Prefix;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSMICCASTAWAY_API UInfoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInfoComponent();

	UFUNCTION(BlueprintPure, Category = "Info")
	FInfoData GetInfoData();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	FInfoData Info;

private:

	TArray<FString> Prefixes
	{
			{"A"}, {"B"}, {"C"}, {"D"}, {"E"}, {"F"}, {"G"},
			{"H"}, {"I"}, {"J"}, {"K"}, {"L"}, {"M"}, {"N"}
	};
};
