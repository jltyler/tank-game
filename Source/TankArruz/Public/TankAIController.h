// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANKARRUZ_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

protected:
	bool SetupTank();
	bool SetupPlayerTank();

public:
	void AimAtPlayer();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Tanks")
	ATank * ControlledTank = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Tanks")
	ATank * PlayerTank = nullptr;
	// ControlledTank will pursue until at least this distance
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Pathfinding")
	float PursueDistance = 7500.0f;
};
