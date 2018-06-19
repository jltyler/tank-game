// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/AimingComponent.h"
#include "Public/TankMovementComponent.h"
#include "TankArruz.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Public/Projectile.h"
#include "Public/TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));
	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
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
	//PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATank::Fire);
}

void ATank::SetupAiming(UStaticMeshComponent * NewBarrelComponent, UStaticMeshComponent * NewTurretComponent, USceneComponent * NewFirePoint)
{
	AimingComponent->SetBarrelComponent(NewBarrelComponent);
	AimingComponent->SetTurretComponent(NewTurretComponent);
	FirePoint = NewFirePoint;
}

void ATank::SetupMovement(UStaticMeshComponent * NewBody, UStaticMeshComponent * NewLeftTrack, UStaticMeshComponent * NewRightTrack)
{
	MovementComponent->SetBody(NewBody);
	MovementComponent->SetLeftTrack(NewLeftTrack);
	MovementComponent->SetRightTrack(NewRightTrack);
}

void ATank::Fire()
{
	if (Reloaded)
	{
		FVector SpawnLocation(FirePoint ? FirePoint->GetComponentLocation() : GetActorLocation());
		FRotator SpawnRotation(FirePoint ? FirePoint->GetComponentRotation() : GetActorRotation());
		AProjectile * Fired = GetWorld()->SpawnActor<AProjectile>(WeaponProjectile, SpawnLocation, FRotator(0.0f), FActorSpawnParameters());
		if (Fired)
		{
			Fired->SetVelocity(AimingComponent->GetAimVector() * LaunchSpeed);
			Reloaded = false;
			FTimerDelegate Callback;
			Callback.BindLambda([this] {this->Reloaded = true; });
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, Callback, ReloadTime, false);
		}
		else
			UE_LOG(LogTankGame, Error, TEXT("Tried to fire but got NULL back!"))
	}
}

bool ATank::IsReloaded() const
{
	return Reloaded;
}

bool ATank::FindTrajectory(const FVector & IdealPosition)
{
	FVector FinalVelocity;

	FVector StartPosition(GetActorLocation());
	if (GetFirePoint()) StartPosition = GetFirePoint()->GetComponentLocation();

	bool ArcFound = UGameplayStatics::SuggestProjectileVelocity(
		this, FinalVelocity, StartPosition, IdealPosition, LaunchSpeed,
		false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (ArcFound)
	{
		FRotator NewRotation = FinalVelocity.Rotation();
		AimingComponent->SetAimPitch(NewRotation.Pitch);
		AimingComponent->SetAimYaw(NewRotation.Yaw);
	}
	return ArcFound;
}

FVector ATank::GetLocation()
{
	return RootComponent->GetComponentLocation();
}

void ATank::SetFirePoint(USceneComponent * NewFirePoint)
{
	FirePoint = NewFirePoint;
}

USceneComponent * ATank::GetFirePoint() const
{
	return FirePoint;
}
