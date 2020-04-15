// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector& HitLocation, float LaunchSpeed){

	if(!Barrel){
		UE_LOG(LogTemp, Error, TEXT("Barrel not found."));
		return;
	}

	auto BarrelLocation = Barrel->GetComponentLocation();

	// Find projectile suggested velocity
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bSuggested = UGameplayStatics::SuggestProjectileVelocity(this, 
												LaunchVelocity, 
												StartLocation, 
												HitLocation, 
												LaunchSpeed, 
												false, 
												0, 
												0, 
												ESuggestProjVelocityTraceOption::DoNotTrace);
	if(bSuggested){
		UE_LOG(LogTemp, Display, TEXT("Launch solution found"));
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from barrel at %s."), *GetOwner()->GetName(), *AimDirection.ToString(), *BarrelLocation.ToString());
		MoveBarrel(AimDirection);
	}

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet){
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet){
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection){
	// Get the difference in the direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();
	auto DeltaRotator = AimDirectionRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("Delta rotator is %s."), *DeltaRotator.ToString());

	// Adjust barrel elevation
	Barrel->Elevate(DeltaRotator.Pitch);
}

