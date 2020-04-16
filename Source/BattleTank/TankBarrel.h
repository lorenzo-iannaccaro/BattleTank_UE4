// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// min -1, max +1
	void Elevate(float RelativeAngularSpeed);

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDegreesPerSecond = 20.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxElevation = 40.f;
	UPROPERTY(EditDefaultsOnly)
	float MinElevation = 0.f;

};
