// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankPlayerController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetPawn(APawn* InPawn) override;
	
protected:
	// How close can the Enemy Tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 10000;

private:
	UFUNCTION()
	void OnPossessedTankDeath();
};
