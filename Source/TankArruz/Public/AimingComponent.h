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

	void UpdateBarrelRotation(float DeltaTime);
	void UpdateTurretRotation(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = Aiming)
	void SetAimYaw(float NewYaw);
	UFUNCTION(BlueprintCallable, Category = Aiming)
	float GetAimPitch() const;
	UFUNCTION(BlueprintCallable, Category = Aiming)
	void SetAimPitch(float NewPitch);
	UFUNCTION(BlueprintCallable, Category = Aiming)
	float GetAimYaw() const;
	UFUNCTION(BlueprintCallable, Category = Aiming)
	bool GetLockedOn() const;

	FVector GetAimVector() const;

	UFUNCTION(BlueprintCallable, Category = References)
	void SetBarrelComponent(UStaticMeshComponent * NewBarrel);
	UFUNCTION(BlueprintCallable, Category = References)
	UStaticMeshComponent * GetBarrelComponent() const;

	UFUNCTION(BlueprintCallable, Category = References)
	void SetTurretComponent(UStaticMeshComponent * NewTurret);
	UFUNCTION(BlueprintCallable, Category = References)
	UStaticMeshComponent * GetTurretComponent() const;


protected:
	UStaticMeshComponent * BarrelComponent = nullptr;
	UStaticMeshComponent * TurretComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Constraints)
	float MinYaw = -180.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Constraints)
	float MaxYaw = 180.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Constraints)
	float YawPerSecond = 25.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Constraints)
	float MinPitch = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Constraints)
	float MaxPitch = 45.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Constraints)
	float PitchPerSecond = 10.0f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Runtime)
	float DesiredYaw = 0.0f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Runtime)
	float DesiredPitch = 0.0f;

	bool LockedOn = false;
};
