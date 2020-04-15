// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeAngularSpeed){

    RelativeAngularSpeed = FMath::Clamp<float>(RelativeAngularSpeed, -1, +1);

    auto ElevationChange = RelativeAngularSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto NewElevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);

    SetRelativeRotation(FRotator(NewElevation, 0, 0));
}