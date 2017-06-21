// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


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