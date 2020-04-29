// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const{
	TArray<ASprungWheel*> WheelsArray;

	// Children is a out parameter
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		WheelsArray.Add(SprungWheel);
	}

	return WheelsArray;
}

void UTankTrack::SetThrottle(float Throttle){
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.0, +1.0);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle){
	auto ForceToApply = TrackMaxDrivingForce * CurrentThrottle;
    auto WheelsArray = GetWheels();

	auto SingleWheelForceIntensity = 0;
	if(WheelsArray.Num() > 0){
		SingleWheelForceIntensity = ForceToApply / WheelsArray.Num();
	}
	for(auto Wheel : WheelsArray){
		Wheel->UpdateWheelForceIntensity(SingleWheelForceIntensity);
	}

}
