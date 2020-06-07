// Fill out your copyright notice in the Description page of Project Settings.


#include "hungerGameStateBase.h"
#include "Net/UnrealNetwork.h"

void AhungerGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AhungerGameStateBase, Winner);
}

void AhungerGameStateBase::OnRep_Winner()
{
	OnWinnerFound.Broadcast();
}
