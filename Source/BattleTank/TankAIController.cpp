// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Viewport.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
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
    if(!AITank){ return; }
    if(!PlayerTank){ return; }

    FVector PlayerHitLocation = PlayerTank->GetActorLocation();

    auto AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)){return;}
    AimingComponent->AimAt(PlayerHitLocation);

    // AI firing
    if(AimingComponent->GetFiringState() == EFiringState::Locked){
        AimingComponent->Fire();
    }

    // AI tank move to the game player's tank
    MoveToActor(PlayerTank, DistanceFromPlayerTank);

}

void ATankAIController::SetPawn(APawn* InPawn){
    Super::SetPawn(InPawn);

    auto PossessedTank = Cast<ATank>(InPawn);
    if (!PossessedTank) { return; }

    // Subscribe our local method to the tank's death event
    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
}

void ATankAIController::OnPossessedTankDeath(){
    UE_LOG(LogTemp, Warning, TEXT("Tank %s has died"), *GetPawn()->GetHumanReadableName());
    GetPawn()->DetachFromControllerPendingDestroy();
}

