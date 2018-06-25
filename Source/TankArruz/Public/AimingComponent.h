// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AimingComponent.generated.h"

class UStaticMeshComponent;
class AProjectile;

UENUM()
enum class ETankFiringStatus : uint8
{
	Reloading,
	Aiming,
	LockedOn
};

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent) )
class TANKARRUZ_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UStaticMeshComponent * NewBarrelComponent, UStaticMeshComponent * NewTurretComponent, USceneComponent * NewFirePoint);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RefreshFiringStatus();

	void UpdateBarrelRotation(float DeltaTime);
	void UpdateTurretRotation(float DeltaTime);

	/// Aiming functions
	// Set desired yaw and pitch for arc to hit AimLocation
	UFUNCTION(BlueprintCallable, Category = "Aiming")
	bool AimAtLocation(const FVector & AimLocation);
	// Fire weapon (if reloaded)
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();
	// Reload weapon
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void SetDesiredYaw(float NewYaw);
	UFUNCTION(BlueprintPure, Category = "Aiming")
	float GetAimYaw() const;

	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void SetDesiredPitch(float NewPitch);
	UFUNCTION(BlueprintPure, Category = "Aiming")
	float GetAimPitch() const;

	UFUNCTION(BlueprintPure, Category = "Aiming")
	bool IsLockedOn() const;
	UFUNCTION(BlueprintPure, Category = "Aiming")
	FVector GetAimVector() const;

	UFUNCTION(BlueprintCallable, Category = "References")
	void SetBarrelComponent(UStaticMeshComponent * NewBarrel);
	UFUNCTION(BlueprintPure, Category = "References")
	UStaticMeshComponent * GetBarrelComponent() const;

	UFUNCTION(BlueprintCallable, Category = "References")
	void SetTurretComponent(UStaticMeshComponent * NewTurret);
	UFUNCTION(BlueprintPure, Category = "References")
	UStaticMeshComponent * GetTurretComponent() const;


protected:
	/// Aiming
	// Barrel mesh to rotate pitch on. projectile velocity is derived from this meshes rotation.
	UStaticMeshComponent * BarrelComponent = nullptr;
	// Turret mesh to rotate yaw on
	UStaticMeshComponent * TurretComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Constraints")
	float MinYaw = -180.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Constraints")
	float MaxYaw = 180.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Constraints")
	float YawPerSecond = 25.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Constraints")
	float MinPitch = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Constraints")
	float MaxPitch = 45.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Constraints")
	float PitchPerSecond = 10.0f;

	// Yaw required for a perfect shot
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Aiming")
	float DesiredYaw = 0.0f;
	// Pitch required for a perfect shot
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Aiming")
	float DesiredPitch = 0.0f;
	// Yaw is at desired value
	bool YawLockedOn = false;
	// Pitch is at desired value
	bool PitchLockedOn = false;

	/// Weapon stuff
	// Projectile launch speed
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon")
	float LaunchSpeed = 3500.f;
	// Time in seconds before Tank can fire again
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon")
	float ReloadTime = 1.4f;
	// AProjectile child class to fire
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AProjectile> WeaponProjectile;
	// Where the projectile spawns when fired (also used as origin for trajectory calculation)
	USceneComponent * FirePoint = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	bool Reloaded = true;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	ETankFiringStatus FiringStatus = ETankFiringStatus::LockedOn;
};
