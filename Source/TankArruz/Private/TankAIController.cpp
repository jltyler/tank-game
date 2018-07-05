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
	if (PlayerTank)
	{
		GetWorldTimerManager().SetTimer(AimingTimerHandle, this, &ATankAIController::AimAtPlayer, 0.5f, true);
		SetActorTickEnabled(true);
	}
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ensure(ControlledTank && PlayerTank))
	{
		auto result = MoveToActor(PlayerTank, PursueDistance, true, true, true);
		//if (result == EPathFollowingRequestResult::Failed) UE_LOG(LogTankGame, Error, TEXT("%s controller failed to pathfind!"), *ControlledTank->GetName())
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ControlledTank = Cast<ATank>(InPawn);
		if (ControlledTank)
		{
			if (PlayerTank)
			{
				GetWorldTimerManager().SetTimer(AimingTimerHandle, this, &ATankAIController::AimAtPlayer, 0.5f, true);
				SetActorTickEnabled(true);
			}
			else
			{
				UE_LOG(LogTankGame, Error, TEXT("%s has no PlayerTank"), *GetName())
			}
			ControlledTank->OnTankDeath.AddDynamic(this, &ATankAIController::OnTankDeath);
			NewTankPossessed(ControlledTank);
		}
		else
		{
			UE_LOG(LogTankGame, Error, TEXT("%s has no ControlledTank"), *GetName())
		}
	}
}

void ATankAIController::OnTankDeath()
{
	GetWorldTimerManager().ClearTimer(AimingTimerHandle);
	ControlledTank->DetachFromControllerPendingDestroy();
	ControlledTank = nullptr;
	SetActorTickEnabled(false);
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