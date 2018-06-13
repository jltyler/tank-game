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

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelComponent(UStaticMeshComponent * NewBarrel);
	UFUNCTION(BlueprintCallable, Category = Getters)
	UStaticMeshComponent * GetBarrelComponent() const;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretComponent(UStaticMeshComponent * NewTurret);
	UFUNCTION(BlueprintCallable, Category = Getters)
	UStaticMeshComponent * GetTurretComponent() const;

protected:
	UStaticMeshComponent * BarrelComponent = nullptr;
	UStaticMeshComponent * TurretComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = Constraints)
	float MinYaw = -180.0f;
	UPROPERTY(BlueprintReadWrite, Category = Constraints)
	float MaxYaw = 180.0f;
	UPROPERTY(BlueprintReadWrite, Category = Constraints)
	float YawPerSecond = 25.0f;

	UPROPERTY(BlueprintReadWrite, Category = Constraints)
	float MinPitch = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = Constraints)
	float MaxPitch = 45.0f;
	UPROPERTY(BlueprintReadWrite, Category = Constraints)
	float PitchPerSecond = 10.0f;

	UPROPERTY(BlueprintReadOnly, Category = Runtime)
	float DesiredYaw = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = Runtime)
	float DesiredPitch = 0.0f;
};
