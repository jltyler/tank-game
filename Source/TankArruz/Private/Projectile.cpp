// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Public/TimerManager.h"

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

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->SetupAttachment(RootComponent);
	ImpactBlast->bAutoActivate = false;
}

void AProjectile::Launch(const float & LaunchSpeed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector(LaunchSpeed, 0.f, 0.f));
	ProjectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	ImpactBlast->Activate();
	LaunchBlast->Deactivate();
	VisibleMesh->SetVisibility(false);
	FTimerHandle DeathTimer;
	GetWorldTimerManager().SetTimer(DeathTimer, this, &AProjectile::Death, 2.5f, false);
}

void AProjectile::Death()
{
	Destroy();
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

