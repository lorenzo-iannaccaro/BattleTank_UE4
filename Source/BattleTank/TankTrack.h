// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Force in kg * cm/s^2
	UPROPERTY(EditDefaultsOnly, Category = Throttle)
	float TrackMaxDrivingForce = 30000000.f;

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	// forward declaration can also be done this way
	TArray<class ASprungWheel*> GetWheels() const;
	
private:
	UTankTrack();

	void DriveTrack(float CurrentThrottle);
	
};
