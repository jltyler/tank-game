// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AimingComponent.generated.h"

class UStaticMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKARRUZ_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetAimYaw(float NewYaw);
	float GetAimPitch() const;
	void SetAimPitch(float NewPitch);

	float GetAimYaw() const;

	void SetBarrelComponent(UStaticMeshComponent * NewBarrel);
	UStaticMeshComponent * GetBarrelComponent() const;
	void SetTurretComponent(UStaticMeshComponent * NewTurret);
	UStaticMeshComponent * GetTurretComponent() const;
	void SetFirePoint(USceneComponent * NewFirePoint);
	USceneComponent * GetFirePoint() const;

protected:
	UStaticMeshComponent * BarrelComponent = nullptr;
	UStaticMeshComponent * TurretComponent = nullptr;
	USceneComponent * FirePoint = nullptr;

	float MinYaw = -180.0f;
	float MaxYaw = 180.0f;
	float YawPerSecond = 25.0f;

	float MinPitch = 0.0f;
	float MaxPitch = 45.0f;
	float PitchPerSecond = 10.0f;

	float DesiredYaw = 0.0f;
	float DesiredPitch = 0.0f;
};
