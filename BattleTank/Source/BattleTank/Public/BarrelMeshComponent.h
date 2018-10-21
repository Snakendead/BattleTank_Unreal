// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BarrelMeshComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UBarrelMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxElevationDegrees = 20.f;

	UPROPERTY(EditDefaultsOnly)
	float MinElevationDegrees = 0.f;
};
