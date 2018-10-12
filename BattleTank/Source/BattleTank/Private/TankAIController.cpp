// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Public/TankAIController.h"
#include "Public/Tank.h"

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("AI Controller tank is empty"))
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("AIController Begin play with tank %s"), *ControlledTank->GetName())

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("AI Controller didn't find player tank"))
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("AIController Begin play with player tank %s"), *PlayerTank->GetName())
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!GetPlayerTank()) { return; }
	if (!GetControlledTank()) { return; }

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
}
