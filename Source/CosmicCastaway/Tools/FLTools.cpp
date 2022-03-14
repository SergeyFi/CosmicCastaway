// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/FLTools.h"

FVector UFLTools::GetRandomSpherePosition()
{
	auto U = FMath::RandRange(0.0f, 1.0f);
	auto X1 = FMath::RandRange(-1000000.0f, 1000000.0f);
	auto X2 = FMath::RandRange(-1000000.0f, 1000000.0f);
	auto X3 = FMath::RandRange(-1000000.0f, 1000000.0f);

	auto Mag = FMath::Sqrt(X1*X1 + X2*X2 + X3*X3);
	
	X1 /= Mag; X2 /= Mag; X3 /= Mag;

	auto C = FMath::Pow(U, float(1.0f/3.0f));
	
	return {X1 * C, X2 * C, X3 * C};
}
