// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
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
		GetControlledTank()->AimAt(HitLocation);
	}
	

}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const{
	// Find crosshair position in screen coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-Project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Linetrace along look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
		return true;
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const {
	FVector CameraWorldLocation;

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection, FVector& OutHitLocation) const {
	FHitResult HitResult;
	FVector Start, End;

	Start = PlayerCameraManager->GetCameraLocation();
	End = Start + LineTraceRange * LookDirection;

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility
		))
	{
		// Set hit location
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}