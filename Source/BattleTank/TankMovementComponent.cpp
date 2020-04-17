// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::InitialiseTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet){
    if(!LeftTrackToSet || !RightTrackToSet){
        return;
    }
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float ControlThrow){
    //UE_LOG(LogTemp, Warning, TEXT("Intend move with throw: %f"), ControlThrow);
    LeftTrack->SetThrottle(ControlThrow);
    RightTrack->SetThrottle(ControlThrow);
}

void UTankMovementComponent::IntendTurnClockwise(float ControlThrow){
    LeftTrack->SetThrottle(ControlThrow);
    RightTrack->SetThrottle(-ControlThrow);
}
