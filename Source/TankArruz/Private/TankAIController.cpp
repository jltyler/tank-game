// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "TankArruz.h"
#include "Public/TimerManager.h"
#include "Public/Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	SetupTank();
	SetupPlayerTank();
	if (ControlledTank && PlayerTank)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATankAIController::AimAtPlayer, 0.5f, true);
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	if (ControlledTank && PlayerTank)
	{
		auto result = MoveToActor(PlayerTank, PursueDistance, true, true, true);
		//if (result == EPathFollowingRequestResult::Failed) UE_LOG(LogTankGame, Error, TEXT("%s controller failed to pathfind!"), *ControlledTank->GetName())
	}
}

bool ATankAIController::SetupTank()
{
	ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank)
	{
		UE_LOG(LogTankGame, Log, TEXT("%s controls tank %s"), *GetName(), *ControlledTank->GetName())
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

void ATankAIController::AimAtPlayer()
{
	if (!PlayerTank || !ControlledTank) return;

	ControlledTank->AimAt(PlayerTank->GetActorLocation());
}