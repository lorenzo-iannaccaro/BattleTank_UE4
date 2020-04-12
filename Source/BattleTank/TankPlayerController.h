// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	private:
		UPROPERTY(EditAnywhere)
		float ReticleXLocation = 0.5f;
		UPROPERTY(EditAnywhere)
		float ReticleYLocation = 0.35f;
		UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0f;

	public:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		ATank* GetControlledTank() const;
		
		void AimTowardsReticle();
		bool GetSightRayHitLocation(FVector&) const;
		bool GetLookVectorHitLocation(FVector, FVector&) const;
	
};
