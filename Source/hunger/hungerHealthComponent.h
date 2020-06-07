// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/*
 *** заготовка для здоровья персонажа
 *** если вы видите этот текст, значит этот функционал не готов
 *** 


*/
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "hungerHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNGER_API UhungerHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UhungerHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Health")
	float BaseHealth;

	UPROPERTY(BlueprintReadOnly)
	float Health;
	

	UFUNCTION()
	void takeDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
