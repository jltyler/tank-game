// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "TankArruz.h"
#include "Public/TimerManager.h"
#include "Public/Tank.h"


void ATankAIController::BeginPlay()
{
	SetActorTickEnabled(false);
	SetupAITank();
	SetupPlayerTank();
	if (ensure(ControlledTank && PlayerTank))
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATankAIController::AimAtPlayer, 0.5f, true);
		SetActorTickEnabled(true);
	}
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	if (ensure(ControlledTank && PlayerTank))
	{
		auto result = MoveToActor(PlayerTank, PursueDistance, true, true, true);
		//if (result == EPathFollowingRequestResult::Failed) UE_LOG(LogTankGame, Error, TEXT("%s controller failed to pathfind!"), *ControlledTank->GetName())
	}
}

bool ATankAIController::SetupAITank()
{
	ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank)
	{
		UE_LOG(LogTankGame, Log, TEXT("%s controls tank %s"), *GetName(), *ControlledTank->GetName())
		return true;
	}
	else return false;
}

bool ATankAIController::SetupPlayerTank()
{
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	return (PlayerTank ? true : false);
}

void ATankAIController::AimAtPlayer()
{
	if (ensure(PlayerTank && ControlledTank))
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
}