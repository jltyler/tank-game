// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankArruz.h"
#include "DrawDebugHelpers.h"

void UTankMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto Vel = Body->GetPhysicsLinearVelocity().GetSafeNormal();
	float Slippage = FVector::DotProduct(Vel, GetOwner()->GetActorRightVector());
	auto CurrLoc = GetOwner()->GetActorLocation();
	DrawDebugLine(GetWorld(), CurrLoc, CurrLoc + Vel * 100, FColor::Emerald, false, -1.0f, 0, 10.0f);
	DrawDebugLine(GetWorld(), CurrLoc, CurrLoc + GetOwner()->GetActorRightVector() * 1000.0f, FColor::Blue, false, -1.0f, 0, 10.0f);
	UE_LOG(LogTankGame, Warning, TEXT("%s.Slippage: %f"), *GetOwner()->GetName(), Slippage)
	Body->AddForce(-Vel * FMath::Abs<float>(Slippage) * SidewaysFrictionMultiplier);
}

void UTankMovementComponent::Initialize(UStaticMeshComponent * NewBody, UStaticMeshComponent * NewLeftTrack, UStaticMeshComponent * NewRightTrack)
{
	Body = NewBody;
	LeftTrack = NewLeftTrack;
	RightTrack = NewRightTrack;
}

void UTankMovementComponent::LeftTrackForward(const float Axis)
{
	if (ensure(Body && LeftTrack)) Body->AddForceAtLocation(Body->GetComponentRotation().Vector() * ForceMultiplier * Axis, LeftTrack->GetComponentLocation());
}

void UTankMovementComponent::RightTrackForward(const float Axis)
{
	if (ensure(Body && RightTrack)) Body->AddForceAtLocation(Body->GetComponentRotation().Vector() * ForceMultiplier * Axis, RightTrack->GetComponentLocation());
}

void UTankMovementComponent::MoveForward(const float Axis)
{
	if (ensure(Body && LeftTrack && RightTrack))
	{
		FVector ForceVector = Body->GetComponentRotation().Vector() * Axis * ForceMultiplier;
		Body->AddForceAtLocation(ForceVector, LeftTrack->GetComponentLocation());
		Body->AddForceAtLocation(ForceVector, RightTrack->GetComponentLocation());
	}
}

void UTankMovementComponent::TurnRight(const float Axis)
{
	if (ensure(Body && LeftTrack && RightTrack))
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
	
	TurnRight(Cross.Size() * FMath::Sign(Cross.Z));
	//DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + Cross *  1000, FColor::White, true, .3f, 0, 15.f);
}

