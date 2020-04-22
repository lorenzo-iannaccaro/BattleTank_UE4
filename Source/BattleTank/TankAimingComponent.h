// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.generated.h"

// Firing states for the reticle color
UENUM()
enum class EFiringState : uint8{
	Locked, 
	Reloading, 
	Aiming,
	NoRoundsLeft
};

// forward declarations
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitialiseTurretAndBarrel(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int RoundsLeft = 10;

public:	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 5000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UClass* ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	void AimAt(FVector& HitLocation);

private:
	FVector AimDirection = FVector(0.0);
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveTurretAndBarrel(FVector AimDirection);

	bool IsBarrelMoving();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};
