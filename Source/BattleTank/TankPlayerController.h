// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Component used for the tank aiming system
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	private:
		UPROPERTY(EditDefaultsOnly)
		float ReticleXLocation = 0.5f;
		UPROPERTY(EditDefaultsOnly)
		float ReticleYLocation = 0.35f;
		UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f;

	protected:
		UFUNCTION(BlueprintImplementableEvent)
		void FindAimingComponent(UTankAimingComponent* AimingComponentReference);

	public:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
		
		void AimTowardsReticle();
		bool GetSightRayHitLocation(FVector&) const;
		bool GetLookVectorHitLocation(FVector, FVector&) const;
	
};
