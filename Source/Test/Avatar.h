// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class APickupItem;

UCLASS()
class TEST_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCharacteristics)
		int32 maxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCharacteristics)
		int32 currentHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCharacteristics)
		float sensitivity = 200.0f;

	void toggleInventory();

	void pickup(APickupItem* item);

	void mouseClicked();

	bool inventoryShowing = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TMap<FString, int> backpack;
	TMap<FString, UTexture2D*> icons;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Moves player
	void moveForward(float amount);
	void moveRight(float amount);
	void moveLeft(float amount);
	void moveBack(float amount);

	void yaw(float amount);
	void pitch(float amount);
};
