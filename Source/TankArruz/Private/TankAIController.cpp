// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "TankArruz.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
		UE_LOG(LogTankGame, Log, TEXT("%s controls tank %s"), *GetName(), *GetControlledTank()->GetName())
	else
		UE_LOG(LogTankGame, Error, TEXT("%s controls NULL tank"), *GetName())
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
