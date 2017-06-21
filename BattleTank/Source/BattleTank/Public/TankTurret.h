// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// between -1 & 1
	void Turn(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Turret Properties")
		float MaxDegreesPerSecond = 20;

};
