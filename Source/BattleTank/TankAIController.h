// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

	private:
		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float DistanceFromPlayerTank = 7500.f;

		virtual void SetPawn(APawn* InPawn) override;

		UFUNCTION()
		void OnPossessedTankDeath();
};
