// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

#include "Public/Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoint = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoint, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0) {
		auto ParticleComponent = FindComponentByClass<UParticleSystemComponent>();
		if (ParticleComponent) {
			UE_LOG(LogTemp, Warning, TEXT("ParticleComponent Exist"))
			ParticleComponent->Activate();
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("ParticleComponent NOT Exist"))
		}
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}
