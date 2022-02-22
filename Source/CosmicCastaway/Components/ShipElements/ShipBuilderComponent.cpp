// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipElements/ShipBuilderComponent.h"

// Sets default values for this component's properties
UShipBuilderComponent::UShipBuilderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UShipBuilderComponent::Build()
{
	if (CurrentBuild.Num() == 0)
	{
		bool bFirstElement = true;
		for (const auto& ElementClass : ShipBuild)
		{
			if (ElementClass)
			{
				if (bFirstElement)
				{
					Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())->SetStaticMesh
					(ElementClass->GetDefaultObject<UStaticMeshComponent>()->GetStaticMesh());

					PrevElement = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
					
					bFirstElement = false;
				}
				else
				{
					auto NewElement = NewObject<UStaticMeshComponent>(GetOwner(), ElementClass);

					if (NewElement)
					{
						NewElement->RegisterComponent();
						NewElement->SetWorldLocation(PrevElement->GetSocketTransform(SocketConnectorName).GetLocation());
					
						FAttachmentTransformRules Rules
						(
							EAttachmentRule::KeepWorld,
							EAttachmentRule::KeepWorld,
							EAttachmentRule::KeepRelative,
							true
						);
						
						NewElement->AttachToComponent(GetOwner()->GetRootComponent(), Rules);
						NewElement->SetWorldLocation(PrevElement->GetSocketTransform(SocketConnectorName).GetLocation());
						PrevElement = NewElement;
					}
				}
			}
		}
	}
}


// Called when the game starts
void UShipBuilderComponent::BeginPlay()
{
	Super::BeginPlay();

	Build();
}
