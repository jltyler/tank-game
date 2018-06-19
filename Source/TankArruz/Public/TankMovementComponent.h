// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */

UCLASS()
class TANKARRUZ_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBody(UStaticMeshComponent * NewBody);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetLeftTrack(UStaticMeshComponent * NewLeftTrack);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetRightTrack(UStaticMeshComponent * NewRightTrack);
	UFUNCTION(BlueprintCallable, Category = Movement)
	void LeftTrackForward(const float Axis);
	UFUNCTION(BlueprintCallable, Category = Movement)
	void RightTrackForward(const float Axis);
	UFUNCTION(BlueprintCallable, Category = Movement)
	void MoveForward(const float Axis);
	UFUNCTION(BlueprintCallable, Category = Movement)
	void TurnRight(const float Axis);

protected:
	UStaticMeshComponent * Body = nullptr;
	UStaticMeshComponent * LeftTrack = nullptr;
	UStaticMeshComponent * RightTrack = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Movement)
	float ForceMultiplier = 4000000.0f;
};
