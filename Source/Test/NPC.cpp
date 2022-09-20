// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include <Test\Avatar.h>
#include <Test\MyHUD.h>

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

ANPC::ANPC(const FObjectInitializer& init) : Super(init)
{

	proxSphere = init.CreateDefaultSubobject<USphereComponent>(this, TEXT("Proximity Sphere"));
	proxSphere->AttachTo(RootComponent);
	proxSphere->SetSphereRadius(100.f);

	NPCMessage = "Slap like now!";
}

void ANPC::Prox_Implementation(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	
	if (Cast<AAvatar>(otherActor) == nullptr)
	{
		return;
	}

	APlayerController* controller = GetWorld()->GetFirstPlayerController();

	if (controller)
	{
		AMyHUD* HUD = controller->GetHUD<AMyHUD>();
		HUD->addMessage(Message(NPCName + " : " + NPCMessage, 5.f, FColor::White, messageIcon));

		AAvatar* player = Cast<AAvatar>(otherActor);
		
		if(player->currentHP > 0)
			player->currentHP -= 10;
	}
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	proxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);

	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

