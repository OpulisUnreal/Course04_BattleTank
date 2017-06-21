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


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}