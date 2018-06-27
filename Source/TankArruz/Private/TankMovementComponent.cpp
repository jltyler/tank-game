// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankArruz.h"
#include "DrawDebugHelpers.h"

void UTankMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto Vel = Body->GetPhysicsLinearVelocity().GetSafeNormal();
	float Slippage = FVector::DotProduct(Vel, GetOwner()->GetActorRightVector());
	Body->AddForce(-Vel * FMath::Abs<float>(Slippage) * SidewaysFrictionMultiplier);
}

void UTankMovementComponent::Initialize(UStaticMeshComponent * NewBody, UStaticMeshComponent * NewLeftTrack, UStaticMeshComponent * NewRightTrack)
{
	Body = NewBody;
	LeftTrack = NewLeftTrack;
	LeftTrack->OnComponentHit.AddDynamic(this, &UTankMovementComponent::OnLeftTrackHit);
	RightTrack = NewRightTrack;
	RightTrack->OnComponentHit.AddDynamic(this, &UTankMovementComponent::OnRightTrackHit);

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
	ForwardDrive = Axis;
}

void UTankMovementComponent::TurnRight(const float Axis)
{
	TurnRightDrive = Axis;
}

void UTankMovementComponent::OnLeftTrackHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (ensure(Body && LeftTrack))
	{
		FVector ForceVector = Body->GetForwardVector() * (ForwardDrive + TurnRightDrive) * ForceMultiplier;
		auto CurrLoc = LeftTrack->GetComponentLocation();
		DrawDebugLine(GetWorld(), CurrLoc, CurrLoc + ForceVector, FColor::Purple, false, -1.f, 0, 10.f);
		Body->AddForceAtLocation(ForceVector, LeftTrack->GetComponentLocation());
	}
}

void UTankMovementComponent::OnRightTrackHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (ensure(Body && RightTrack))
	{
		FVector ForceVector = Body->GetForwardVector() * (ForwardDrive - TurnRightDrive) * ForceMultiplier;
		auto CurrLoc = RightTrack->GetComponentLocation();
		DrawDebugLine(GetWorld(), CurrLoc, CurrLoc + ForceVector * 10, FColor::Purple, false, -1.f, 0, 10.f); 
		Body->AddForceAtLocation(ForceVector, RightTrack->GetComponentLocation());
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

