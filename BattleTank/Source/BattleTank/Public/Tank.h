// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UBarrelMeshComponent;
class UTurretMeshComponent;
class AProjectileActor;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Set)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Set)
	void SetBarrelReference(UBarrelMeshComponent* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Set)
	void SetTurretReference(UTurretMeshComponent* TurretToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;
	
private:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectileActor> ProjectileBlueprint; 

	UBarrelMeshComponent* Barrel = nullptr;

	float LastFireTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ReloadTimeInSeconds = 2.f;
};
