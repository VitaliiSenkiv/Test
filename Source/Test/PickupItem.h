// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"

#include "PickupItem.generated.h"

UCLASS()
class TEST_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();

	APickupItem(const FObjectInitializer& init);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		FString name = "unknown item";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		int32 quantity = 0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
		USphereComponent* proxSphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
		UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		UTexture2D* icon;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
		void Prox(UPrimitiveComponent* hitedPrimitive, AActor* otherActor, UPrimitiveComponent* otherPrimitive,
			int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
