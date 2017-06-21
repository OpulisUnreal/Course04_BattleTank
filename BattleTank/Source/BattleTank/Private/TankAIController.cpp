// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto Tank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Tank) {
		auto ControlledTank = Cast<ATank>(GetPawn());
		// TODO Move towards the player

		// Aim towards the player
		ControlledTank->AimAt(Tank->GetActorLocation());

		// Fire if ready
		ControlledTank->Fire();
	}
	
}