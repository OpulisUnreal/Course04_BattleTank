// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	auto OurTankName = GetOwner()->GetName();
	if (!Barrel) return;
	auto BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());

	FVector OutLaunchVelocity;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")), // fallback to Barrel location
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s barrel aiming at: %s"), *OurTankName, *AimDirection.ToString());

		MoveBarrelTowards(AimDirection);
	}

	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	// Get Tank Rotation
	// Calculate Barrel Offset Rotations
		// Turret as yaw from AimDirection.(X|Y)
		// Barrel as pitch from AimDirection.Z

	// Work out difference between current Barrel rotation & AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5); //TODO: Remove MagicNumber

}