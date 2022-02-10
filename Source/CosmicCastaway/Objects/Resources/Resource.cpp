// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Resources/Resource.h"

float UResource::GetMolarMass()
{
	return MolarMass;
}

const TArray<FResourceValue>& UResource::GetDecompProducts()
{
	return DecompProducts;
}

float UResource::GetSplittingEnergy()
{
	return SplittingEnergy;
}
