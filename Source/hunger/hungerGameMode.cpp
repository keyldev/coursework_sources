

#include "hungerGameMode.h"
#include "hungerHUD.h"
#include "hungerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "hungerPlayerController.h"
#include "hungerPlayerState.h"
#include "hungerGameStateBase.h"

AhungerGameMode::AhungerGameMode()
	: Super()
{
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// худ
	HUDClass = AhungerHUD::StaticClass();
}

void AhungerGameMode::PostLogin(APlayerController* NewPlayer) // игрок подключился = массив игроков пополнился
{
	Super::PostLogin(NewPlayer);

	AlivePlayers.Add(Cast <AhungerPlayerController>(NewPlayer));
}

void AhungerGameMode::PlayerDied(AhungerCharacter* Killed, AhungerCharacter* Killer) // игрок умер
{
	if (Killed)
	{

		if (AhungerPlayerController* PC = Cast<AhungerPlayerController>(Killed->GetController()))
		{
			AlivePlayers.RemoveSingle(PC);
		}

		if (AlivePlayers.Num() == 1 && AlivePlayers.IsValidIndex(0)) // логика игры, если остался последний игрок -> он победитель
		{
			FoundWinner(Cast <AhungerPlayerState>(AlivePlayers[0]->PlayerState));
		}

	}
}

void AhungerGameMode::FoundWinner(AhungerPlayerState* Winner) // поиск победителя
{

	if (AhungerGameStateBase* GS = GetGameState<AhungerGameStateBase>())
	{
		GS->Winner = Winner;
	}
}
