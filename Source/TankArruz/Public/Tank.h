// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UAimingComponent;
class AProjectile;
class UTankMovementComponent;

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

	UFUNCTION(BlueprintCallable, Category = AimingSetup)
	void SetupAiming(UStaticMeshComponent * NewBarrelComponent, UStaticMeshComponent * NewTurretComponent, USceneComponent * NewFirePoint);

	UFUNCTION(BlueprintCallable, Category = MovementSetup)
	void SetupMovement(UStaticMeshComponent * NewBody, UStaticMeshComponent * NewLeftTrack, UStaticMeshComponent * NewRightTrack);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void Fire();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool IsReloaded() const;
	// Set point at which the Tank will attempt to fire at
	bool FindTrajectory(const FVector & IdealPosition);
	UFUNCTION(BlueprintCallable)
	FVector GetLocation();

	UFUNCTION(BlueprintCallable, Category = TurretSetup)
	void SetFirePoint(USceneComponent * NewFirePoint);
	UFUNCTION(BlueprintCallable, Category = TurretInfo)
	USceneComponent * GetFirePoint() const;

protected:
	/// Weapon stuff
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Turret)
	UAimingComponent * AimingComponent = nullptr;
	// Projectile launch speed for trajectory calculation
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Weapon)
	float LaunchSpeed = 3500.f;
	// Time in seconds before Tank can fire again
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Weapon)
	float ReloadTime = 1.4f;
	// AProjectile child class to fire
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Weapon)
	TSubclassOf<AProjectile> WeaponProjectile;
	// Where the projectile spawns when fired
	USceneComponent * FirePoint = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	bool Reloaded = true;

	/// Movement stuff
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Movement)
	UTankMovementComponent * MovementComponent = nullptr;
	// Body mesh to use for movement
	UStaticMeshComponent * Body = nullptr;
	// Left Track to use for movement
	UStaticMeshComponent * LeftTrack = nullptr;
	// Right Track to use for movement
	UStaticMeshComponent * RightTrack = nullptr;

	// Force multiplier when moving forwards or backwards
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Movement)
	float ForwardForce = 4000000.0f;
	// Force multiplier when turning left or right
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Movement)
	float TurnForce = 4000000.0f;

};
