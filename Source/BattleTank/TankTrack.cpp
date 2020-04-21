// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay(){
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle){
	CurrentThrottle = CurrentThrottle + FMath::Clamp<float>(Throttle, -1.0, +1.0);
}

// When hit persists, gets called every frame
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("A track hit something."))
	DriveTrack();
	RemoveSlidingCounterforce();
	CurrentThrottle = 0.0;
}

void UTankTrack::RemoveSlidingCounterforce(){
	// Work-out the required acceleration this frame to correct
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = - SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack(){
	auto ForceToApply = GetForwardVector() * TrackMaxDrivingForce * CurrentThrottle;
    auto LocationToApply = GetComponentLocation();
    auto RootComponent = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());

    RootComponent->AddForceAtLocation(ForceToApply, LocationToApply);
}
