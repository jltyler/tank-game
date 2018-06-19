// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankArruz.h"
#include "DrawDebugHelpers.h"

void UTankMovementComponent::SetBody(UStaticMeshComponent * NewBody)
{
	Body = NewBody;
}

void UTankMovementComponent::SetLeftTrack(UStaticMeshComponent * NewLeftTrack)
{
	LeftTrack = NewLeftTrack;
}

void UTankMovementComponent::SetRightTrack(UStaticMeshComponent * NewRightTrack)
{
	RightTrack = NewRightTrack;
}

void UTankMovementComponent::LeftTrackForward(const float Axis)
{
	if (Body && LeftTrack) Body->AddForceAtLocation(Body->GetComponentRotation().Vector() * ForceMultiplier * Axis, LeftTrack->GetComponentLocation());
}

void UTankMovementComponent::RightTrackForward(const float Axis)
{
	if (Body && RightTrack) Body->AddForceAtLocation(Body->GetComponentRotation().Vector() * ForceMultiplier * Axis, RightTrack->GetComponentLocation());
}

void UTankMovementComponent::MoveForward(const float Axis)
{
	if (Body && LeftTrack && RightTrack)
	{
		FVector ForceVector = Body->GetComponentRotation().Vector() * Axis * ForceMultiplier;
		Body->AddForceAtLocation(ForceVector, LeftTrack->GetComponentLocation());
		Body->AddForceAtLocation(ForceVector, RightTrack->GetComponentLocation());
	}
}

void UTankMovementComponent::TurnRight(const float Axis)
{
	if (Body && LeftTrack && RightTrack)
	{
		FVector ForceVector = Body->GetComponentRotation().Vector() * Axis * ForceMultiplier * TurnForceMultiplier;
		Body->AddForceAtLocation(ForceVector, LeftTrack->GetComponentLocation());
		Body->AddForceAtLocation(-ForceVector, RightTrack->GetComponentLocation());
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto MoveUnit = MoveVelocity.GetSafeNormal();
	auto ActorUnit = GetOwner()->GetActorForwardVector();
	auto Dot = FVector::DotProduct(MoveUnit, ActorUnit);
	MoveForward(Dot);
	auto Cross = FVector::CrossProduct(MoveUnit, ActorUnit);
	TurnRight(Cross.Z); // TODO: rotate so cross z points directly up
}
