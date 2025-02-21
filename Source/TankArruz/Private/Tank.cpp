// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "TankArruz.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	HitPoints = MaxHitPoints;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	HitPoints -= DamageAmount;
	if (HitPoints <= 0)
	{
		OnTankDeath.Broadcast();
		StopFiring();
		Death();
	}
	return DamageAmount;
}

float ATank::GetHealthAlpha() const
{
	return HitPoints / MaxHitPoints;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATank::Fire);
}