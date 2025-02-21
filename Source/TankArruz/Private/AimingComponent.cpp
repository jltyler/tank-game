// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/AimingComponent.h"
#include "TankArruz.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Public/Projectile.h"
#include "Public/TimerManager.h"

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
}

void UAimingComponent::Initialize(UStaticMeshComponent * NewBarrelComponent, UStaticMeshComponent * NewTurretComponent, USceneComponent * NewFirePoint)
{
	BarrelComponent = NewBarrelComponent;
	TurretComponent = NewTurretComponent;
	FirePoint = NewFirePoint;
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ensure(BarrelComponent)) UpdateBarrelRotation(DeltaTime);
	if (ensure(TurretComponent)) UpdateTurretRotation(DeltaTime);
}

void UAimingComponent::UpdateBarrelRotation(float DeltaTime)
{
	auto WorldPitch = BarrelComponent->GetComponentRotation().Pitch;
	auto Diff = DesiredPitch - WorldPitch;
	if (Diff < -180) Diff += 360;
	if (Diff > 180) Diff -= 360;
	auto TurnSpeed = PitchPerSecond * DeltaTime;
	if (FMath::Abs<float>(Diff) < TurnSpeed)
	{ 
		float NewPitch = FMath::Clamp<float>(BarrelComponent->RelativeRotation.Pitch + Diff, MinPitch, MaxPitch);
		BarrelComponent->SetRelativeRotation(FRotator(NewPitch, 0.f, 0.f));
		PitchLockedOn = true;
	}
	else
	{
		float NewPitch = FMath::Clamp<float>(BarrelComponent->RelativeRotation.Pitch + FMath::Sign(Diff) * TurnSpeed, MinPitch, MaxPitch);
		BarrelComponent->SetRelativeRotation(FRotator(NewPitch, 0.f, 0.f));
		PitchLockedOn = false;
	}
}

void UAimingComponent::UpdateTurretRotation(float DeltaTime)
{
	auto Yaw = TurretComponent->GetComponentRotation().Yaw;
	auto Diff = DesiredYaw - Yaw;
	if (Diff < -180) Diff += 360;
	if (Diff > 180) Diff -= 360;
	auto TurnSpeed = YawPerSecond * DeltaTime;
	if (FMath::Abs<float>(Diff) < TurnSpeed)
	{
		TurretComponent->AddLocalRotation(FRotator(0.0f, Diff, 0.0f));
		YawLockedOn = true;
	}
	else
	{
		TurretComponent->AddLocalRotation(FRotator(0.0f, FMath::Sign(Diff) * TurnSpeed, 0.0f));
		YawLockedOn = false;
	}
}

bool UAimingComponent::AimAtLocation(const FVector & AimLocation)
{
	FVector StartPosition(FirePoint ? FirePoint->GetComponentLocation() : GetOwner()->GetActorLocation());

	FVector FinalVelocity;
	bool ArcFound = UGameplayStatics::SuggestProjectileVelocity(
		this, FinalVelocity, StartPosition, AimLocation, LaunchSpeed,
		PreferHighArc, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	// If no trajectory path found, aim directly at AimLocation
	FRotator NewRotation = (ArcFound ? FinalVelocity.Rotation() : (AimLocation - StartPosition).Rotation());
	DesiredPitch = NewRotation.Pitch;
	DesiredYaw = NewRotation.Yaw;

	return ArcFound;
}

void UAimingComponent::FireProjectile()
{
	if (!Reloaded || Ammo == 0) return;
	FVector SpawnLocation(FirePoint ? FirePoint->GetComponentLocation() : GetOwner()->GetActorLocation());
	FRotator SpawnRotation(BarrelComponent ? BarrelComponent->GetComponentRotation() : GetOwner()->GetActorRotation());
	AProjectile * Fired = GetWorld()->SpawnActor<AProjectile>(WeaponProjectile, SpawnLocation, SpawnRotation, FActorSpawnParameters());
	if (Fired)
	{
		Fired->Launch(LaunchSpeed);
		Reloaded = false;
		FTimerHandle TimerHandle;
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UAimingComponent::Reload, ReloadTime);
		--Ammo;
	}
	else
		UE_LOG(LogTankGame, Error, TEXT("%s.%s failed to spawn projectile!"), *GetOwner()->GetName(), *GetName())
}

void UAimingComponent::StartFiring()
{
	IsFiring = true;
	FireProjectile();
}

void UAimingComponent::StopFiring()
{
	IsFiring = false;
}

void UAimingComponent::Reload()
{
	Reloaded = true;
	if (Refire && IsFiring) FireProjectile();
}

inline int32 UAimingComponent::GetAmmo() const
{
	return Ammo;
}

ETankFiringStatus UAimingComponent::GetFiringStatus() const
{
	if (!Reloaded) return ETankFiringStatus::Reloading;
	else if (Ammo == 0) return ETankFiringStatus::NoAmmo;
	else if (YawLockedOn && PitchLockedOn) return ETankFiringStatus::LockedOn;
	else return ETankFiringStatus::Aiming;
}

inline void UAimingComponent::SetDesiredYaw(float NewYaw)
{
	DesiredYaw = NewYaw;
	//DesiredYaw = FMath::Clamp<float>(NewYaw, MinYaw, MaxYaw);
}

inline float UAimingComponent::GetAimPitch() const
{
	return BarrelComponent ? BarrelComponent->GetComponentRotation().Pitch : 0.0f;
}

inline void UAimingComponent::SetDesiredPitch(float NewPitch)
{
	DesiredPitch = NewPitch;
	//DesiredPitch = FMath::Clamp<float>(NewPitch, MinPitch, MaxPitch);
}

inline float UAimingComponent::GetAimYaw() const
{
	return TurretComponent ? TurretComponent->GetComponentRotation().Yaw : 0.0f;
}

inline bool UAimingComponent::IsLockedOn() const
{
	return YawLockedOn && PitchLockedOn;
}

inline FVector UAimingComponent::GetAimVector() const
{
	return BarrelComponent ? BarrelComponent->GetComponentRotation().Vector() : FVector(0.0f, 0.0f, 90.0f);
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
