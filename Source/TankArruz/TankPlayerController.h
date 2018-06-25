// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANKARRUZ_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	ATank * FindPlayerTank() const;
	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	ATank * ControlledTank = nullptr;
	
	void FindAimPointV();
	bool FindAimPoint();
	bool AimTrace(const FVector & Location, const FVector & Direction, const float length);
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float AimTraceLength = 20000.0f;

};
