// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Public/TankAIController.h"
#include "Public/Tank.h"

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) { return; }
	if (!GetControlledTank()) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	GetControlledTank()->Fire();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
}
