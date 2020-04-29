// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SceneComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0 && !Dead)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank died"))
		OnDeath.Broadcast();
		Dead = true;
	}
	return DamageToApply;
}

float ATank::GetHealthPercentage() const{
	return (float)CurrentHealth / (float)StartingHealth;
}



