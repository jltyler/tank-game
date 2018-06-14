// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankArruz.h"
#include "Public/Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Public/TimerManager.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = FindPlayerTank();
	if (ControlledTank)
		UE_LOG(LogTankGame, Log, TEXT("%s controls tank %s"), *GetName(), *ControlledTank->GetName())
	else
		UE_LOG(LogTankGame, Error, TEXT("%s(%d).ControlledTank is NULL!"), *GetName(), GetUniqueID())

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATankPlayerController::FindAimPointV, 0.2f, true);

}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

ATank * ATankPlayerController::FindPlayerTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::FindAimPointV()
{
	FindAimPoint();
}

bool ATankPlayerController::FindAimPoint()
{
	int32 vx, vy;
	GetViewportSize(vx, vy);
	FVector PLocation, PDirection;
	if (DeprojectScreenPositionToWorld(.5 * vx, .5 * vy, PLocation, PDirection))
	{
		//DrawDebugLine(GetWorld(), PLocation, PLocation + PDirection * AimTraceLength, FColor::Emerald, true, 1.0f, 0, 30.0f);
		return AimTrace(PLocation, PDirection, AimTraceLength);
	}
	return false;
}

bool ATankPlayerController::AimTrace(const FVector & StartLocation, const FVector & Direction, const float length)
{
	FHitResult HitResult;
	FVector EndLocation = StartLocation + Direction * length;
	FCollisionQueryParams CQuery;
	CQuery.AddIgnoredActor(GetPawn());
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_WorldStatic, CQuery);
	if (Hit) EndLocation = HitResult.Location;
	DrawDebugSphere(GetWorld(), EndLocation, 100.0f, 8, Hit ? FColor::Emerald : FColor::Red, true, 1.5f, 0, 5.0f);
	ControlledTank->FindTrajectory(EndLocation);
	return Hit;
}
