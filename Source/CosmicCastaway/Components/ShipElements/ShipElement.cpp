// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipElements/ShipElement.h"

void UShipElement::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable)
	{
		FString Message;
		auto DataPtr = DataTable->FindRow<FElementData>(DataID, Message);

		if (DataPtr)
		{
			SetStaticMesh(DataPtr->Mesh);
		}
	}
}
