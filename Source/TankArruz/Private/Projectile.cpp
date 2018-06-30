// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement"));
	Movement->bAutoActivate = false;
	//Movement->bRotationFollowsVelocity = true;
}

void AProjectile::Launch(const float & LaunchSpeed)
{
	Movement->SetVelocityInLocalSpace(FVector(LaunchSpeed, 0.f, 0.f));
	Movement->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

