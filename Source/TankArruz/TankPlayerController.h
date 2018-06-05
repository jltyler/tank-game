// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

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

	ATank * GetControlledTank() const;
	ATank * ControlledTank = nullptr;
	
	void AimTowardsCrosshair();
	bool GetCameraTraceLocation(FHitResult & out_HitResult);
};
