// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Viewport.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    auto AITank = GetPawn();
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    if(!ensure(PlayerTank)){ return; }
    FVector PlayerHitLocation = PlayerTank->GetActorLocation();
    //AITank->AimAt(PlayerHitLocation);
    auto AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)){return;}
    AimingComponent->AimAt(PlayerHitLocation);

    // TODO fix AI firing
    //AITank->Fire();

    // AI tank move to the game player's tank
    MoveToActor(PlayerTank, DistanceFromPlayerTank);

}

