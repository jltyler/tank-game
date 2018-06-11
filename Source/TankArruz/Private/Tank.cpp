// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/AimingComponent.h"
#include "TankArruz.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetAimPoint(const FVector & Position)
{
	AimingComponent->SetAimPoint(Position);
}



FVector ATank::GetAimPoint() const
{
	return AimingComponent->GetAimPoint();
}

FVector ATank::GetLocation()
{
	return RootComponent->GetComponentLocation();
}

void ATank::SetBarrelComponent(UStaticMeshComponent * NewBarrel)
{
	AimingComponent->BarrelComponent = NewBarrel;
}

UStaticMeshComponent * ATank::GetBarrelComponent() const
{
	return AimingComponent->BarrelComponent;
}

void ATank::SetTurretComponent(UStaticMeshComponent * NewTurret)
{
	AimingComponent->TurretComponent = NewTurret;
}

UStaticMeshComponent * ATank::GetTurretComponent() const
{
	return AimingComponent->TurretComponent;
}
