// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "GameFramework/Pawn.h"
#include "Engine/World.h"

#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankMovementComponent.h"
#include "Public/BarrelMeshComponent.h"
#include "Public/TurretMeshComponent.h"
#include "Public/ProjectileActor.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UBarrelMeshComponent * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTurretMeshComponent * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire() {
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!isReloaded) { return; }
	LastFireTime = FPlatformTime::Seconds();

	if (!Barrel) { return; }


	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator Rotator = Barrel->GetSocketRotation(FName("Projectile"));;

	auto Projectile = GetWorld()->SpawnActor<AProjectileActor>(ProjectileBlueprint, StartLocation, Rotator);
	Projectile->LaunchProjectile(LaunchSpeed);
}