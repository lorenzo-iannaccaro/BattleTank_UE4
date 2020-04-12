// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay(){
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Inside begin play of TankPlayerController"));

    auto ControlledTank = GetControlledTank();
    if(!ControlledTank){
        UE_LOG(LogTemp, Error, TEXT("No tank possessed by player."));
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("Possessed tank is: %s"), *ControlledTank->GetName());

}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardsReticle();

}

ATank* ATankPlayerController::GetControlledTank() const{
    return Cast<ATank> (GetPawn());
}

void ATankPlayerController::AimTowardsReticle(){
    if(!GetControlledTank()){
        UE_LOG(LogTemp, Error, TEXT("No player tank pawn detected."));
        return;
    }
    FVector HitLocation;
    if(GetSightRayHitLocation(HitLocation)){
        UE_LOG(LogTemp, Warning, TEXT("Hit something at location %s"), *HitLocation.ToString());
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
        //UE_LOG(LogTemp, Warning, TEXT("World direction: %s"), *WorldDirection.ToString());

        // Linetrace and see if something is hit
        if(GetLookVectorHitLocation(WorldDirection, HitLocation)){
            //UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
        }
    }
    

    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLoc) const{

    FHitResult HitResult;
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)){
        HitLoc = HitResult.Location;
        return true;
    }
    HitLoc = FVector(0.0);
    return false;
}