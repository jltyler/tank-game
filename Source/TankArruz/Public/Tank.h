// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UAimingComponent;

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
	FVector GetAimPoint() const;
	FVector GetLocation();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelComponent(UStaticMeshComponent * NewBarrel);
	UFUNCTION(BlueprintCallable, Category = Setup)
	UStaticMeshComponent * GetBarrelComponent() const;
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretComponent(UStaticMeshComponent * NewTurret);
	UFUNCTION(BlueprintCallable, Category = Setup)
	UStaticMeshComponent * GetTurretComponent() const; 

protected:
	FVector AimPoint;
	UAimingComponent * AimingComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	float LaunchSpeed = 3500.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AimYawSpeed = 25.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AimPitchSpeed = 10.0f;
};
