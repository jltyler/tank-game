// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankArruz.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Public/TimerManager.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	if (ControlledTank)
		UE_LOG(LogTankGame, Log, TEXT("%s controls tank %s"), *GetName(), *GetControlledTank()->GetName())
	else
		UE_LOG(LogTankGame, Error, TEXT("%s(%d).ControlledTank is NULL!"), *GetName(), GetUniqueID())

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATankPlayerController::AimTowardsCrosshair, 1.f, true);

}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FHitResult TraceHitResult;
	GetCameraTraceLocation(TraceHitResult);
}

bool ATankPlayerController::GetCameraTraceLocation(FHitResult & out_HitResult)
{
	FVector StartLocation;
	FRotator Rotation;
	GetPlayerViewPoint(StartLocation, Rotation);
	FVector EndLocation(StartLocation + Rotation.Vector() * 10000);
	bool Hit = GetWorld()->LineTraceSingleByChannel(out_HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_WorldStatic);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(0, 0, 255), true, .5f, 0, 10.f);
	return Hit;
}