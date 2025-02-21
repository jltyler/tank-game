// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class TANKARRUZ_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	/// Setup
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UStaticMeshComponent * NewBody, UStaticMeshComponent * NewLeftTrack, UStaticMeshComponent * NewRightTrack);

	/// Movement
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void LeftTrackForward(const float Axis);
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void RightTrackForward(const float Axis);
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveForward(const float Axis);
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void TurnRight(const float Axis);

	/// Physics
	UFUNCTION()
	void OnLeftTrackHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);
	UFUNCTION()
	void OnRightTrackHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	/// AI
	void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;
	//void RequestPathMove(const FVector & MoveVelocity) override;
protected:
	UStaticMeshComponent * Body = nullptr;
	UStaticMeshComponent * LeftTrack = nullptr;
	UStaticMeshComponent * RightTrack = nullptr;

	float LeftDrive = 0.0f;
	float RightDrive = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement")
	float ForceMultiplier = 2000000.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement")
	float TurnForceMultiplier = 1.3f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement")
	float SidewaysFrictionMultiplier = 2000000.0f;

};
