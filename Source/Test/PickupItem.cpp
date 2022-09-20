// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"
#include "Avatar.h"
#include "MyHUD.h"

// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

APickupItem::APickupItem(const FObjectInitializer& init) :Super(init)
{
	proxSphere = init.CreateDefaultSubobject<USphereComponent>(this, TEXT("Prox Sphere"));
	mesh = init.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));

	RootComponent = mesh;
	mesh->SetSimulatePhysics(true);

	proxSphere->AttachTo(RootComponent);
}

void APickupItem::Prox_Implementation(UPrimitiveComponent* hitedPrimitive, AActor* otherActor,
	UPrimitiveComponent* otherPrimitive, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	AAvatar* player = Cast<AAvatar>(otherActor);
	if (player == nullptr)
	{
		return;
	}

	player->pickup(this);

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	if (controller)
	{
		AMyHUD* HUD = controller->GetHUD<AMyHUD>();

		HUD->addMessage(Message(FString("Picked up ") + FString::FromInt(quantity) + ' ' + name, 10, 
			FColor::White, icon));
	}

	Destroy();
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	proxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);

	Super::BeginPlay();
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



