// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "hungerProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "hungerCharacter.h"
#include "hungerGameMode.h"

AhungerProjectile::AhungerProjectile() 
{
	// Коллизия пули
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AhungerProjectile::OnHit);		

	
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Ставим родительским компонентом
	RootComponent = CollisionComp;

	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// через 3 секунды после выстрела, снаряд будет пропадать 
	InitialLifeSpan = 3.0f;

	SetReplicates(true);
	SetReplicateMovement(true);
}

void AhungerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		if (AhungerCharacter* HitPlayer = Cast<AhungerCharacter>(OtherActor))
		{
			if (AhungerGameMode* GM = Cast <AhungerGameMode>(GetWorld()->GetAuthGameMode()))
			{
				AhungerCharacter* Killer = Cast <AhungerCharacter>(GetOwner());
				GM->PlayerDied(HitPlayer, Killer); // при попадении снаряда в игрока - он умирает -> вычёркивается из массива выживших игроков

				HitPlayer->Killer = Killer;
				HitPlayer->OnRep_Killer();
			}
		}
	}
}