// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Viewport.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    ATank* AITank = Cast<ATank> (GetPawn());
    ATank* PlayerTank = Cast<ATank> (GetWorld()->GetFirstPlayerController()->GetPawn());

    if(PlayerTank){
        FVector PlayerHitLocation = PlayerTank->GetActorLocation();
        AITank->AimAt(PlayerHitLocation);

        // AI firing
        AITank->Fire();
    }

    // AI tank move to the game player's tank
    MoveToActor(PlayerTank, DistanceFromPlayerTank);

}

