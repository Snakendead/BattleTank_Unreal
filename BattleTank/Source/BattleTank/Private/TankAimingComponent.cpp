// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Public/TankAimingComponent.h"
#include "Public/BarrelMeshComponent.h"
#include "Public/TurretMeshComponent.h"
#include "Public/ProjectileActor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AmmoLeft == 0) {
		FiringStatus = EFiringStatus::EmptyAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (isBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
	// ...
}

void UTankAimingComponent::Initialize(UBarrelMeshComponent * BarrelToSet, UTurretMeshComponent * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

bool UTankAimingComponent::isBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01f);
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim) {

	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		WorldSpaceAim,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (!bHaveAimSolution) {
		UE_LOG(LogTemp, Warning, TEXT("No solution for %s"), *GetOwner()->GetName())
		return;
	}

	AimDirection = OutLaunchVelocity.GetSafeNormal();
	MoveBarrelTowards(AimDirection);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire() {

	if (FiringStatus == EFiringStatus::Reloading) { return; }
	if (FiringStatus == EFiringStatus::EmptyAmmo) { return; }

	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }
	
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator Rotator = Barrel->GetSocketRotation(FName("Projectile"));;

	auto Projectile = GetWorld()->SpawnActor<AProjectileActor>(ProjectileBlueprint, StartLocation, Rotator);
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = GetWorld()->GetTimeSeconds();

	AmmoLeft -= 1;
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}
