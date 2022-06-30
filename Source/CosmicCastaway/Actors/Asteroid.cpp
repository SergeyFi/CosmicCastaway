// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Asteroid.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>("AsteroidMesh");
	RootComponent = AsteroidMesh;
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	RandomRotation = UKismetMathLibrary::RandomRotator();

	Randomize();

	GenerateOre();

	Sleep();
}

void AAsteroid::SetChildCollision(bool bCollision)
{
	TArray<USceneComponent*> ChildsComp;
	
	GetRootComponent()->GetChildrenComponents(false, ChildsComp);

	for (auto ChildsMesh : ChildsComp)
	{
		if (ChildsMesh->GetOwner() != this)
		{
			ChildsMesh->GetOwner()->SetActorEnableCollision(bCollision);
		}
	}
}

void AAsteroid::Randomize()
{
	if (AsteroidMeshes.Num() != 0)
	{
		auto RandomMesh = AsteroidMeshes[FMath::RandRange(0, AsteroidMeshes.Num()-1)];
		Cast<UStaticMeshComponent>(RootComponent)->SetStaticMesh(RandomMesh);
	}
	
	SetActorRotation(UKismetMathLibrary::RandomRotator(true));

	auto RandomScale = FMath::RandRange(ScaleMin, ScaleMax);
	SetActorScale3D({RandomScale, RandomScale, RandomScale});
}

void AAsteroid::GenerateOre()
{
	if (OresInfo.Num() != 0)
	{
		auto SocketNames = AsteroidMesh->GetAllSocketNames();

		auto RandomOreCount = FMath::RandRange(0, MaxOreCount);

		for (auto i = 0; i < RandomOreCount; ++i)
		{
			auto RandomIndex = FMath::RandRange(0, SocketNames.Num() - 1);
			
			auto Ore = GetWorld()->SpawnActor<AOre>(GetRandomOreClass(), AsteroidMesh->GetSocketTransform(SocketNames[RandomIndex]));
			
			Ore->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform, SocketNames[RandomIndex]);

			SocketNames.RemoveAt(RandomIndex);
		}
	}
}

TSubclassOf<AOre> AAsteroid::GetRandomOreClass()
{
	TArray<int32> Chances;

	int32 Sum = 0;

	for (auto OreInfo : OresInfo)
	{
		Sum += OreInfo.SpawnChance;

		Chances.Add(Sum);
	}

	auto Chance = FMath::RandRange(0, Chances.Last());

	for (auto i = 0; i < Chances.Num();++i)
	{
		if (Chance <= Chances[i])
		{
			return OresInfo[i].OreClass;
		}
	}

	return OresInfo[0].OreClass;
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(RandomRotation * DeltaTime * RotationSpeed);
}

void AAsteroid::Sleep()
{
	SetActorTickEnabled(false);

	SetChildCollision(false);

	bIsSleep = true;
}

void AAsteroid::WakeUp()
{
	SetActorTickEnabled(true);

	SetChildCollision(true);

	bIsSleep = false;
}

bool AAsteroid::IsSleep()
{
	return bIsSleep;
}

