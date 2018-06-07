// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/AimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankArruz.h"


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

	// ...
	
}


// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAimingComponent::SetAimPoint(const FVector & Position)
{
	AimPoint = Position;
	if (!BarrelComponent)
	{
		UE_LOG(LogTankGame, Error, TEXT("%s.AimingComponent.BarrelComponent is NULL!"), *GetOwner()->GetName())
		return;
	}
	FVector BarrelLocation = BarrelComponent->GetComponentLocation();
	UE_LOG(LogTankGame, Log, TEXT("%s.AimingComponent.SetAimPoint( %s ) Barrel: %s"), *GetOwner()->GetName(), *Position.ToCompactString(), *BarrelLocation.ToString())
}

