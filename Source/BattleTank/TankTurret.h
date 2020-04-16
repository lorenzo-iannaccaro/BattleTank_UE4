// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// min -1, max +1
	void Rotate(float RelativeAngularSpeed);

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDegreesPerSecond = 40.f;
	
};
