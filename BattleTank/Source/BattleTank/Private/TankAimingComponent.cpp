// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();

	Ammo = MaxAmmo;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Ammo <= 0) {
		FiringState = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringState = EFiringStatus::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}

}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	auto OurTankName = GetOwner()->GetName();
	if (!ensure(Barrel && Turret)) { return; }
	auto BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());

	FVector OutLaunchVelocity;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")), // fallback to Barrel location
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards();
	}

	
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::MoveBarrelTowards() {
	if (!ensure(Barrel && Turret)) { return; }

	// Work out difference between current Barrel rotation & AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	
	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180) 
	{
		Turret->Turn(DeltaRotator.Yaw);
	}
	else 
	{
		Turret->Turn(-DeltaRotator.Yaw);
	}

	//float intPart;
	//float fracPart = FMath::Modf(DeltaRotator.Yaw / 360.f, &intPart);
	//float Yaw = fracPart * 360.0f;
	//
	//if (Yaw > 180.0f) {
	//	Yaw -= 360.0f;
	//}
	//else if (Yaw < -180.0f) {
	//	Yaw += 360.0f;
	//}

	////UE_LOG(LogTemp, Warning, TEXT("%s Turns turret with: %f"), *(GetOwner()->GetName()), Yaw);
	//Turret->Turn(Yaw);
}

void UTankAimingComponent::Fire() {
	if (FiringState != EFiringStatus::Reloading && FiringState != EFiringStatus::OutOfAmmo) {
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		Ammo--;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01);
}