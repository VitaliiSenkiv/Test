// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SphereComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Avatar.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AEnemy::AEnemy(const FObjectInitializer& init) :Super(init)
{
	speed = 20.f;
	HP = 100.f;
	experience = 15;
	BPLoot = nullptr;
	baseAttackDamage = 10.f;
	attackTimeout = 1.f;
	timeSinceLastAttack = 0.f;

	sightSphere = init.CreateDefaultSubobject<USphereComponent>(this, TEXT("Sight sphere"));
	attackRangeSphere = init.CreateDefaultSubobject<USphereComponent>(this, TEXT("Attack range sphere"));

	sightSphere->AttachTo(RootComponent);
	attackRangeSphere->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AEnemy::isInSightRange(float distance)
{
	return distance < sightSphere->GetScaledSphereRadius();
}

bool AEnemy::isInAttackRange(float distance)
{
	return distance < attackRangeSphere->GetScaledSphereRadius();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AAvatar* player = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (!player)
	{
		return;
	}

	FVector toPlayer = player->GetActorLocation() - this->GetActorLocation();
	float distance = toPlayer.Size();
	toPlayer.Normalize();

	if (isInSightRange(distance))
	{
		AddMovementInput(toPlayer, speed * DeltaTime, true);

		FRotator toPlayerRotation = toPlayer.Rotation();
		toPlayerRotation.Pitch = 0;

		RootComponent->SetWorldRotation(toPlayerRotation);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}