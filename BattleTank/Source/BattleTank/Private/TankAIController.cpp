// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto playerTank = GetPlayerTank();
	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController didn't find Player Tank"));
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("AI Controller found Player Tank : %s"), *(playerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto Tank = GetPlayerTank();
	if (Tank) {
		// TODO Move towards the player

		// Aim towards the player
		GetControlledTank()->AimAt(Tank->GetActorLocation());

		// Fire if ready
	}
	
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController) {
		return nullptr;
	}
	
	return (Cast<ATankPlayerController>(PlayerController))->GetControlledTank();
}