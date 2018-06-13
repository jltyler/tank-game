// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/AimingComponent.h"
#include "TankArruz.h"
#include "Classes/Kismet/GameplayStatics.h"


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

void ATank::SetBarrelComponent(UStaticMeshComponent * NewBarrel)
{
	AimingComponent->SetBarrelComponent(NewBarrel);
}

UStaticMeshComponent * ATank::GetBarrelComponent() const
{
	return AimingComponent->GetBarrelComponent();
}

void ATank::SetTurretComponent(UStaticMeshComponent * NewTurret)
{
	AimingComponent->SetTurretComponent(NewTurret);
}

UStaticMeshComponent * ATank::GetTurretComponent() const
{
	return AimingComponent->GetTurretComponent();
}

void ATank::SetFirePoint(USceneComponent * NewFirePoint)
{
	FirePoint = NewFirePoint;
}

USceneComponent * ATank::GetFirePoint() const
{
	return FirePoint;
}