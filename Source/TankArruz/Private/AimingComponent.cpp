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
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (BarrelComponent) UpdateBarrelRotation(DeltaTime);
	if (TurretComponent) UpdateTurretRotation(DeltaTime);
}

void UAimingComponent::UpdateBarrelRotation(float DeltaTime)
{
	auto WorldPitch = BarrelComponent->GetComponentRotation().Pitch;
	auto Diff = DesiredPitch - WorldPitch;
	if (Diff < -180) Diff += 360;
	if (Diff > 180) Diff -= 360;
	auto TurnSpeed = PitchPerSecond * DeltaTime;
	if (FMath::Abs<float>(Diff) < TurnSpeed)
		BarrelComponent->AddLocalRotation(FRotator(Diff, 0.0f, 0.0f));
	else
		BarrelComponent->AddLocalRotation(FRotator(FMath::Sign(Diff) * TurnSpeed, 0.0f, 0.0f));
}

void UAimingComponent::UpdateTurretRotation(float DeltaTime)
{
	auto Yaw = TurretComponent->GetComponentRotation().Yaw;
	auto Diff = DesiredYaw - Yaw;
	if (Diff < -180) Diff += 360;
	if (Diff > 180) Diff -= 360;
	auto TurnSpeed = YawPerSecond * DeltaTime;
	if (FMath::Abs<float>(Diff) < TurnSpeed)
		TurretComponent->AddLocalRotation(FRotator(0.0f, Diff, 0.0f));
	else
		TurretComponent->AddLocalRotation(FRotator(0.0f, FMath::Sign(Diff) * TurnSpeed, 0.0f));
}

inline void UAimingComponent::SetAimYaw(float NewYaw)
{
	DesiredYaw = NewYaw;
	//DesiredYaw = FMath::Clamp<float>(NewYaw, MinYaw, MaxYaw);
}

inline float UAimingComponent::GetAimPitch() const
{
	return BarrelComponent ? BarrelComponent->GetComponentRotation().Pitch : 0.0f;
}

inline void UAimingComponent::SetAimPitch(float NewPitch)
{
	DesiredPitch = NewPitch;
	//DesiredPitch = FMath::Clamp<float>(NewPitch, MinPitch, MaxPitch);
}

inline float UAimingComponent::GetAimYaw() const
{
	return TurretComponent ? TurretComponent->GetComponentRotation().Yaw : 0.0f;
}

inline FVector UAimingComponent::GetAimVector() const
{
	return BarrelComponent ? BarrelComponent->GetComponentRotation().Vector() : FVector(0);
}

inline void UAimingComponent::SetBarrelComponent(UStaticMeshComponent * NewBarrel)
{
	BarrelComponent = NewBarrel;
}

inline UStaticMeshComponent * UAimingComponent::GetBarrelComponent() const
{
	return BarrelComponent;
}

inline void UAimingComponent::SetTurretComponent(UStaticMeshComponent * NewTurret)
{
	TurretComponent = NewTurret;
}

inline UStaticMeshComponent * UAimingComponent::GetTurretComponent() const
{
	return TurretComponent;
}
