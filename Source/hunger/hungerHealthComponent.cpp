
#include "hungerHealthComponent.h"
/*
 *** заготовка для здоровья персонажа
 *** если вы видите этот текст, значит этот функционал не готов
 *** 


*/

UhungerHealthComponent::UhungerHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
	BaseHealth = 100.0;
	Health = BaseHealth;
	
}



void UhungerHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UhungerHealthComponent::takeDamage);
		
	}
}

void UhungerHealthComponent::takeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, BaseHealth);
}



