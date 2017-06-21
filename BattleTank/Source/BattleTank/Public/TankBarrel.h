// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Holds parameters for TankBarrel
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ( "Collision" ))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void Elevate(float DegreesPerSecond);
	
private:
	UPROPERTY(EditAnywhere, Category = "Barrel Properties")
		float MaxDegreesPerSecond = 20;

	UPROPERTY(EditAnywhere, Category = "Barrel Properties")
		float MaxElevation = 35;

	UPROPERTY(EditAnywhere, Category = "Barrel Properties")
		float MinElevation = 0;
};
