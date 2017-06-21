// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto tank = GetControlledTank();
	if (!tank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not posessing a tank"));
	}else{
	
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank : %s"), *(tank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation)) { // Has side-effect: is going to line trace
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		
		//TODO Tell ControlledTank to aim at this point
	}
	

}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const{
	// Get Player Camera
	
	// Get Camera Location & Forward Vector
	// Linetrace between Location & Location + (<maxDistance>*ForwardVector)
	// If Hit
		// Store Hit location in HitLocation Out parameter
		// return true
	// Else
		// return false

	HitLocation = FVector(1.0);
	return true;
}