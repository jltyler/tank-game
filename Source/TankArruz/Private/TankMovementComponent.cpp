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
	LeftDrive += Axis;
	RightDrive += Axis;
}

void UTankMovementComponent::TurnRight(const float Axis)
{
	LeftDrive += Axis;
	RightDrive -= Axis;
}

void UTankMovementComponent::OnLeftTrackHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (ensure(Body && LeftTrack))
	{
		FVector ForceVector = Body->GetForwardVector() * FMath::Clamp<float>(LeftDrive, -1.f, 1.f) * ForceMultiplier;
		Body->AddForceAtLocation(ForceVector, LeftTrack->GetComponentLocation());
		LeftDrive = 0.f;
	}
}

void UTankMovementComponent::OnRightTrackHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (ensure(Body && RightTrack))
	{
		FVector ForceVector = Body->GetForwardVector() * FMath::Clamp<float>(RightDrive, -1.f, 1.f) * ForceMultiplier;
		Body->AddForceAtLocation(ForceVector, RightTrack->GetComponentLocation());
		RightDrive = 0.f;
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//UE_LOG(LogTankGame, Log, TEXT("%s.RequestDirectMove(%s)"), *GetOwner()->GetName(), *MoveVelocity.ToString())
	auto MoveUnit = MoveVelocity.GetSafeNormal();
	auto AboveActor = GetOwner()->GetActorLocation() + FVector(0.f, 0.f, 200.f);
	DrawDebugLine(GetWorld(), AboveActor, AboveActor + MoveUnit *  1000, FColor::White, true, .3f, 0, 15.f);
	auto ActorUnit = GetOwner()->GetActorForwardVector();
	auto Dot = FVector::DotProduct(MoveUnit, ActorUnit);
	MoveForward(Dot);
	auto Cross = FVector::CrossProduct(MoveUnit, ActorUnit);
	
	TurnRight(FVector::DotProduct(MoveUnit, GetOwner()->GetActorRightVector()));
	//TurnRight(Cross.Size() * FMath::Sign(Cross.Z));
}

