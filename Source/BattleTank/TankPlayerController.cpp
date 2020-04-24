// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay(){
    Super::BeginPlay();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)){
        UE_LOG(LogTemp, Error, TEXT("Aiming component not found"));
        return; 
    }
    FindAimingComponent(AimingComponent);

}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardsReticle();

}

void ATankPlayerController::SetPawn(APawn* InPawn){
    Super::SetPawn(InPawn);

    auto PossessedTank = Cast<ATank>(InPawn);
    if (!ensure(PossessedTank)) { return; }

    // Subscribe our local method to the tank's death event
    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
}

void ATankPlayerController::AimTowardsReticle(){
    if(!ensure(GetPawn())){
        UE_LOG(LogTemp, Error, TEXT("No player tank pawn detected."));
        return;
    }
    FVector HitLocation;
    if(GetSightRayHitLocation(HitLocation)){
        auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
        if(!ensure(AimingComponent)){ return; }
        
        AimingComponent->AimAt(HitLocation);
    }

}

// True if linetrace hit something; location out-variable is updated by reference
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const{

    // Get viewport size
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    // Get reticle location on screen
    FVector2D ReticleLocation = FVector2D(ViewportSizeX * ReticleXLocation, ViewportSizeY * ReticleYLocation);

    // Deproject to world coordinates
    FVector WorldLocation, WorldDirection;
    if(DeprojectScreenPositionToWorld(ReticleLocation.X, ReticleLocation.Y, WorldLocation, WorldDirection)){
        // Linetrace and see if something is hit
        if(GetLookVectorHitLocation(WorldDirection, HitLocation)){
            return true;
        }
    }

    return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLoc) const{

    FHitResult HitResult;
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera)){
        HitLoc = HitResult.Location;
        return true;
    }
    HitLoc = FVector(0.0);
    return false;
}

void ATankPlayerController::OnPossessedTankDeath(){
    UE_LOG(LogTemp, Warning, TEXT("Player Tank %s has died"), *GetPawn()->GetHumanReadableName());
    StartSpectatingOnly();
}