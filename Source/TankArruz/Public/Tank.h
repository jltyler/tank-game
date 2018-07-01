// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Called by TankControllers with a FVector location to aim at
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Aiming")
	void AimAt(const FVector & AimLocation);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void StartFiring();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void StopFiring();

	UFUNCTION(BlueprintPure, Category = "Tank")
	float GetHealthAlpha() const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Tank")
	float MaxHitPoints = 200.f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Tank")
	float HitPoints = MaxHitPoints;
};
