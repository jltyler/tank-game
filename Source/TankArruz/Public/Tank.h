// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Public/AimingComponent.h"
#include "Tank.generated.h"

UCLASS()
class TANKARRUZ_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Set point at which the Tank will attempt to fire at
	void SetAimPoint(const FVector & Position);
	UFUNCTION(BlueprintCallable)
	FVector GetAimPoint() const { return AimingComponent->GetAimPoint(); }
	FVector GetLocation();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelComponent(UStaticMeshComponent * NewBarrel) { AimingComponent->BarrelComponent = NewBarrel; }
	UFUNCTION(BlueprintCallable, Category = Setup)
	UStaticMeshComponent * GetBarrelComponent() { return AimingComponent->BarrelComponent; }
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretComponent(UStaticMeshComponent * NewTurret) { AimingComponent->TurretComponent = NewTurret; }
	UFUNCTION(BlueprintCallable, Category = Setup)
	UStaticMeshComponent * GetTurretComponent() { return AimingComponent->TurretComponent; }

protected:
	FVector AimPoint;
	UAimingComponent * AimingComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	float LaunchSpeed = 1000.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AimYawSpeed = 30.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AimPitchSpeed = 30.0f;
};
