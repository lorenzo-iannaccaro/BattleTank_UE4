// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::BeginPlay(){
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds){
		FiringState = EFiringState::Reloading;
	}else if(IsBarrelMoving()){
		FiringState = EFiringState::Aiming;
	}else{
		FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const{
	return FiringState;
}

void UTankAimingComponent::AimAt(FVector& HitLocation){

	if(!ensure(Barrel)){
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
		//UE_LOG(LogTemp, Display, TEXT("Launch solution found"));
		AimDirection = LaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from barrel at %s."), *GetOwner()->GetName(), *AimDirection.ToString(), *BarrelLocation.ToString());
		MoveTurretAndBarrel(AimDirection);
	}

}

void UTankAimingComponent::InitialiseTurretAndBarrel(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet){
	if(!ensure(TurretToSet && BarrelToSet)){
		return;
	}

	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveTurretAndBarrel(FVector AimDirection){
	if(!ensure(Turret && Barrel)){
		return;
	}

	// Get the difference in the direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();
	auto DeltaRotator = AimDirectionRotator - BarrelRotator;

	// Adjust turret and barrel to current aim location in 3D space
	if(FMath::Abs(DeltaRotator.Yaw) < 180.0){
		Turret->Rotate(DeltaRotator.Yaw);
	}else{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::Fire(){
	if(!ensure(Barrel)){ return; }

	if(FiringState != EFiringState::Reloading){
		if(!ensure(ProjectileBlueprint)){ return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
											Barrel->GetSocketLocation(FName("Projectile")), 
											Barrel->GetSocketRotation(FName("Projectile")));

		if(!ensure(Projectile)){ return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		FiringState = EFiringState::Reloading;
		LastFireTime = FPlatformTime::Seconds();
	}
	
}

bool UTankAimingComponent::IsBarrelMoving(){
	if(Barrel->GetForwardVector().Equals(AimDirection, 0.01)){
		return false;
	}
	return true;
}

