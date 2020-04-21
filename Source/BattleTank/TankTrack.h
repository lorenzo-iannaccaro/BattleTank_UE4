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
	
private:
	UTankTrack();

	float CurrentThrottle = 0.0;

	virtual void BeginPlay() override;

	void DriveTrack();
	void RemoveSlidingCounterforce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
};
