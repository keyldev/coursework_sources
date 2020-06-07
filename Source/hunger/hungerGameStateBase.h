// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "hungerGameStateBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFoundWinner);
/**
 * 
 */
UCLASS()
class HUNGER_API AhungerGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
		UPROPERTY(ReplicatedUsing = OnRep_Winner, Transient, BlueprintReadOnly, Category = "Game State")
		class AhungerPlayerState* Winner = nullptr;
	UFUNCTION()
		void OnRep_Winner();

	UPROPERTY(BlueprintAssignable, Category = "Game State")
		FFoundWinner OnWinnerFound;
};
