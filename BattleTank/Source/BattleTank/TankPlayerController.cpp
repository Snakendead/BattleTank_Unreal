// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "Engine/World.h"

#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimRowardsCrosshair();
}

void ATankPlayerController::AimRowardsCrosshair() {

	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	FVector HitLocation; //Out param

	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (!bGotHitLocation) {
		return;
	}

	AimingComponent->AimAt(HitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; // to be discarded
	
	return DeprojectScreenPositionToWorld(ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

 bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	float LineTraceRange = 100.f * 100.f * 100.f; // 10km

	FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = Hit.Location;
		return true;
	}

	return false;
}

 void ATankPlayerController::SetPawn(APawn * InPawn)
 {
	 Super::SetPawn(InPawn);
	 if (!InPawn) { return; }

	 auto PossessedTank = Cast<ATank>(InPawn);
	 if (!ensure(PossessedTank)) { return; }

	 PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::TankDeath);
 }

 void ATankPlayerController::TankDeath() {
	 StartSpectatingOnly();
 }
