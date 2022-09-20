// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


#include "Enemy.generated.h"

class USphereComponent;

UCLASS()
class TEST_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	AEnemy(const FObjectInitializer& init);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyProperties)
		float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyProperties)
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyProperties)
		int32 experience;// experience which player gain

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyProperties)
		UClass* BPLoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyProperties)
		float baseAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyProperties)
		float attackTimeout;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyProperties)
		float timeSinceLastAttack;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		USphereComponent* sightSphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		USphereComponent* attackRangeSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	inline bool isInSightRange(float distance);
	inline bool isInAttackRange(float distance);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
