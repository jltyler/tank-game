// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "TankArruz.h"
#include "Public/TimerManager.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	SetupTank();
	SetupPlayerTank();
	if (ControlledTank && PlayerTank)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATankAIController::AimAtPlayer, 1.f, true);
	}

}

bool ATankAIController::SetupTank()
{
	ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank)
	{
		UE_LOG(LogTankGame, Log, TEXT("%s controls tank %s"), *GetName(), *GetControlledTank()->GetName())
		return true;
	}
	else
	{
		UE_LOG(LogTankGame, Error, TEXT("%s controls NULL tank"), *GetName())
		return false;
	}
}

bool ATankAIController::SetupPlayerTank()
{
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		UE_LOG(LogTankGame, Log, TEXT("%s found player tank %s"), *GetName(), *PlayerTank->GetName())
		return true;
	}
	else
	{
		UE_LOG(LogTankGame, Error, TEXT("%s could not find player tank!"), *GetName())
		return false;
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimAtPlayer()
{
	if (!PlayerTank || !ControlledTank) return;

	ControlledTank->SetAimPoint(PlayerTank->GetActorLocation());
}