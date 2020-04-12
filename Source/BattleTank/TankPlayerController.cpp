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

ATank* ATankPlayerController::GetControlledTank() const{
    return Cast<ATank> (GetPawn());
}