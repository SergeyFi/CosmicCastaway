// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Statuses/StatusMining.h"

UStatusMining::UStatusMining()
{
	bInternal = false;
	Status = FText::FromString("Mining");
}
