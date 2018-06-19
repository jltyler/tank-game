// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"
#include "Components/StaticMeshComponent.h"

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
		FVector ForceVector = Body->GetComponentRotation().Vector() * Axis * ForceMultiplier;
		Body->AddForceAtLocation(ForceVector, LeftTrack->GetComponentLocation());
		Body->AddForceAtLocation(-ForceVector, RightTrack->GetComponentLocation());
	}
}
