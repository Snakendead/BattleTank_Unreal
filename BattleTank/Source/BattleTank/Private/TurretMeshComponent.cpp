// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TurretMeshComponent.h"
#include "Engine/World.h"

void UTurretMeshComponent::Rotate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, RawNewElevation, 0));
}