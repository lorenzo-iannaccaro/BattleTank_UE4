// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SceneComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

/* void ATank::AimAt(FVector& HitLocation){
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetName(), *HitLocation.ToString());
	if(!ensure(TankAimingComponent)){ return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
} */

void ATank::Fire(){
	bool bReloaded = ( FPlatformTime::Seconds() - LastFireTime ) > ReloadTimeInSeconds;

	if(Barrel && bReloaded){
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
										Barrel->GetSocketLocation(FName("Projectile")), 
										Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
	
}

