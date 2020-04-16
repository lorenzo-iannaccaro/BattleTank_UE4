// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle){
    UE_LOG(LogTemp, Warning, TEXT("%s throttling: %f"), *GetName(), Throttle);

    auto ForceToApply = GetForwardVector() * TrackMaxDrivingForce * Throttle;
    auto LocationToApply = GetComponentLocation();
    auto RootComponent = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());

    RootComponent->AddForceAtLocation(ForceToApply, LocationToApply);
}
