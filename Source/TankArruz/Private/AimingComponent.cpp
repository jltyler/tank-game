// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/AimingComponent.h"
#include "TankArruz.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!BarrelComponent)
	UE_LOG(LogTankGame, Error, TEXT("%s aiming component has NULL BarrelComponent"), *GetOwner()->GetName())
	if (!TurretComponent)
	UE_LOG(LogTankGame, Error, TEXT("%s aiming component has NULL TurretComponent"), *GetOwner()->GetName())
	if (!FirePoint)
	UE_LOG(LogTankGame, Error, TEXT("%s aiming component has NULL FirePoint"), *GetOwner()->GetName())
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (BarrelComponent)
	{
		auto Pitch = BarrelComponent->GetComponentRotation().Pitch;
		auto Diff = DesiredPitch - Pitch;
		auto TurnSpeed = PitchPerSecond * DeltaTime;
		if (FMath::Abs<float>(Diff) < TurnSpeed)
			BarrelComponent->AddLocalRotation(FRotator(Diff, 0.0f, 0.0f));
		else
			BarrelComponent->AddLocalRotation(FRotator(FMath::Sign(Diff) * TurnSpeed, 0.0f, 0.0f));
	}

	if (TurretComponent)
	{
		auto Yaw = TurretComponent->GetComponentRotation().Yaw;
		auto Diff = DesiredYaw - Yaw;
		auto TurnSpeed = YawPerSecond * DeltaTime;
		if (FMath::Abs<float>(Diff) < TurnSpeed)
			TurretComponent->AddLocalRotation(FRotator(0.0f, Diff, 0.0f));
		else
			TurretComponent->AddLocalRotation(FRotator(0.0f, FMath::Sign(Diff) * TurnSpeed, 0.0f));
	}
}

void UAimingComponent::SetAimYaw(float NewYaw)
{
	DesiredYaw = FMath::Clamp<float>(NewYaw, MinYaw, MaxYaw);
}

float UAimingComponent::GetAimPitch() const
{
	return BarrelComponent->GetComponentRotation().Pitch;
}

void UAimingComponent::SetAimPitch(float NewPitch)
{
	DesiredPitch = FMath::Clamp<float>(NewPitch, MinPitch, MaxPitch);
}

float UAimingComponent::GetAimYaw() const
{
	return BarrelComponent->GetComponentRotation().Yaw;
}

void UAimingComponent::SetBarrelComponent(UStaticMeshComponent * NewBarrel)
{
	BarrelComponent = NewBarrel;
}

UStaticMeshComponent * UAimingComponent::GetBarrelComponent() const
{
	return BarrelComponent;
}

void UAimingComponent::SetTurretComponent(UStaticMeshComponent * NewTurret)
{
	TurretComponent = NewTurret;
}

UStaticMeshComponent * UAimingComponent::GetTurretComponent() const
{
	return TurretComponent;
}

void UAimingComponent::SetFirePoint(USceneComponent * NewFirePoint)
{
	FirePoint = NewFirePoint;
}

USceneComponent * UAimingComponent::GetFirePoint() const
{
	return FirePoint;
}