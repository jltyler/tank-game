// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class TANKARRUZ_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Launch(const float & LaunchSpeed);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent * ProjectileMovement = nullptr;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	USphereComponent * CollisionMesh = nullptr;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UStaticMeshComponent * VisibleMesh = nullptr;
};
