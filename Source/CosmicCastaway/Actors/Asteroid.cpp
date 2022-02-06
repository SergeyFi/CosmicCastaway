// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Asteroid.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	RandomRotation = UKismetMathLibrary::RandomRotator();

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

