// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"

#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	
public:
	ATank();

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	virtual void BeginPlay() override;

	FTankDelegate OnDeath;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 CurrentHealth;
};
