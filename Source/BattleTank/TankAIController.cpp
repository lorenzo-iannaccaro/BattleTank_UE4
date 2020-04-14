// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Viewport.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Inside begin play of TankAIController"));

    auto ControlledTank = GetControlledTank();
    UE_LOG(LogTemp, Warning, TEXT("AI possessed tank is: %s"), *ControlledTank->GetName());

    auto PlayerControlledTank = GetPlayerControlledTank();
    UE_LOG(LogTemp, Warning, TEXT("The human player's tank is: %s"), *PlayerControlledTank->GetName());

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(GetPlayerControlledTank()){
        FVector PlayerHitLocation = GetPlayerControlledTank()->GetActorLocation();
        GetControlledTank()->AimAt(PlayerHitLocation);
    }

}

ATank* ATankAIController::GetControlledTank() const{
    ATank* Tank = Cast<ATank> (GetPawn());
    if(!Tank){
        UE_LOG(LogTemp, Error, TEXT("No tank possessed by AI controller %s."), *GetOwner()->GetName());
        return nullptr;
    }
    return Tank;
}

ATank* ATankAIController::GetPlayerControlledTank() const{
    APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!PlayerPawn){
        UE_LOG(LogTemp, Error, TEXT("Cannot get human player controller."));
        return nullptr;
    }
    return Cast<ATank> (PlayerPawn);
}
