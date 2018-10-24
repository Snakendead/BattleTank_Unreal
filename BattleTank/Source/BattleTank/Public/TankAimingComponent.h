// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 {
	Aiming,
	Reloading,
	Locked
};

class UBarrelMeshComponent;
class UTurretMeshComponent;
class AProjectileActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UBarrelMeshComponent* BarrelToSet, UTurretMeshComponent* TurretToSet);

	void AimAt(FVector WorldSpaceAim);
	void MoveBarrelTowards(FVector AimDirection);
	
	UFUNCTION(BlueprintCallable, Category = "Set")
	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Locked;

private:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sets default values for this component's properties
	UTankAimingComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectileActor> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ReloadTimeInSeconds = 2.f;

	UTurretMeshComponent* Turret;
	UBarrelMeshComponent* Barrel;

	float LastFireTime = 0.f;
};
