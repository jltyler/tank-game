// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<USphereComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Visible Mesh"));
	VisibleMesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projetile Movement"));
	ProjectileMovement->bAutoActivate = false;

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->SetupAttachment(RootComponent);
}

void AProjectile::Launch(const float & LaunchSpeed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector(LaunchSpeed, 0.f, 0.f));
	ProjectileMovement->Activate();
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

