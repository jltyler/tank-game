// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKARRUZ_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;

protected:
	bool SetupTank();

	bool SetupPlayerTank();

public:
	ATank * GetControlledTank() const;
	ATank * GetPlayerTank() const;

	void AimAtPlayer();

protected:
	ATank * ControlledTank = nullptr;
	ATank * PlayerTank = nullptr;
};
