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

	/// Setup
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBody(UStaticMeshComponent * NewBody);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetLeftTrack(UStaticMeshComponent * NewLeftTrack);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetRightTrack(UStaticMeshComponent * NewRightTrack);

	/// Movement
	UFUNCTION(BlueprintCallable, Category = Movement)
	void LeftTrackForward(const float Axis);
	UFUNCTION(BlueprintCallable, Category = Movement)
	void RightTrackForward(const float Axis);
	UFUNCTION(BlueprintCallable, Category = Movement)
	void MoveForward(const float Axis);
	UFUNCTION(BlueprintCallable, Category = Movement)
	void TurnRight(const float Axis);

	/// AI
	void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;
	//void RequestPathMove(const FVector & MoveVelocity) override;
protected:
	UStaticMeshComponent * Body = nullptr;
	UStaticMeshComponent * LeftTrack = nullptr;
	UStaticMeshComponent * RightTrack = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Movement)
	float ForceMultiplier = 2000000.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Movement)
	float TurnForceMultiplier = 1.3f;
};
