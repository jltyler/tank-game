// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankArruz.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	if (ControlledTank)
		UE_LOG(LogTankGame, Log, TEXT("%s controls tank %s"), *GetName(), *GetControlledTank()->GetName())
	else
		UE_LOG(LogTankGame, Error, TEXT("%s(%d).ControlledTank is NULL!"), *GetName(), GetUniqueID())

}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
