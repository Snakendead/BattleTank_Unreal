// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Public/TankAIController.h"
#include "Public/Tank.h"

#include "Public/TankAimingComponent.h"

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!PlayerTank) { return; }
	if (!ensure(ControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (!InPawn) { return; }

	auto PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) { return; }

	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::TankDeath);
}

void ATankAIController::TankDeath() {
	GetPawn()->DetachFromControllerPendingDestroy();
}
