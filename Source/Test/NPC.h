// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/SphereComponent.h"

#include "NPC.generated.h"

UCLASS()
class TEST_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	ANPC(const FObjectInitializer& init);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
		FString NPCMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
		FString NPCName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
		UTexture2D* messageIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
		USphereComponent* proxSphere;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
		void Prox(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp,
			int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
