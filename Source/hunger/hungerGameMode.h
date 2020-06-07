// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "hungerGameMode.generated.h"

UCLASS(minimalapi)
class AhungerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AhungerGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	void PlayerDied(class AhungerCharacter* Killed, class AhungerCharacter* Killer);

	void FoundWinner(class AhungerPlayerState* Winner);

	UPROPERTY(Transient)
		TArray<class AhungerPlayerController*> AlivePlayers; // массив с выжившими игроками
};



