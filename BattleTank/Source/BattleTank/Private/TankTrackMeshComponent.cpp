// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackMeshComponent.h"
#include "Engine/World.h"

UTankTrackMeshComponent::UTankTrackMeshComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrackMeshComponent::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"))
	OnComponentHit.AddDynamic(this, &UTankTrackMeshComponent::OnHit);
}

void UTankTrackMeshComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	AppleSidewayForce();
	CurrentThrottle = 0.0f;
}

void UTankTrackMeshComponent::AppleSidewayForce()
{
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrackMeshComponent::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, +1);
}

void UTankTrackMeshComponent::DriveTrack() {
	auto Name = GetName();

	auto ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

