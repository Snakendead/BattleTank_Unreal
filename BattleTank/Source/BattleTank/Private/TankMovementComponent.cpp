// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Public/TankTrackMeshComponent.h"

void UTankMovementComponent::Initialize(UTankTrackMeshComponent* LeftTrackToSet, UTankTrackMeshComponent* RigthTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RigthTrack = RigthTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(LeftTrack || RigthTrack)) {
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RigthTrack->SetThrottle(Throw);

	//TODO: Prevent double speed
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!ensure(LeftTrack || RigthTrack)) {
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RigthTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector();

	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	auto TurnThrow = FVector::CrossProduct(AIForwardIntention, TankForward);
	IntendMoveForward(ForwardThrow);
	IntendTurnRight(TurnThrow.Z);
}
