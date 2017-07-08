// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

// Depends on TankMovementComponent via pathfinding system (ATankAIController::MoveToActor() -> TankMovementComponent::RequestDirectMove())

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	auto ControlledTank = GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (ensure(PlayerTank && AimingComponent)) {
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		if (AimingComponent->GetFiringState() == EFiringStatus::Locked) {
			AimingComponent->Fire();
		}
	}
	
}