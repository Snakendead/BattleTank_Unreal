// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackMeshComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrackMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 40000000.f; // unit - newtons

private:

	void AppleSidewayForce();
	void DriveTrack();
	float CurrentThrottle = 0.f;

	UTankTrackMeshComponent();
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
