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

	// Called by TankControllers with a FVector location to aim at
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Aiming")
	void AimAt(const FVector & AimLocation);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void StartFiring();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void StopFiring();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
