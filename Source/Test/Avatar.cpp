// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "PickupItem.h"
#include "MyHUD.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AAvatar::moveForward);
	PlayerInputComponent->BindAxis("Right", this, &AAvatar::moveRight);
	PlayerInputComponent->BindAxis("Left", this, &AAvatar::moveLeft);
	PlayerInputComponent->BindAxis("Back", this, &AAvatar::moveBack);

	PlayerInputComponent->BindAxis("Yaw", this, &AAvatar::yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &AAvatar::pitch);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::toggleInventory);
	PlayerInputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::mouseClicked);

	//Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAvatar::moveForward(float amount)
{

	if (inventoryShowing)
	{
		return;
	}
	if (Controller && amount)
	{
		FVector fwd = GetActorForwardVector();

		//AddMovementInput moves actor in fwd direction
		AddMovementInput(fwd, amount);
	}
}

void AAvatar::moveRight(float amount)
{
	if (inventoryShowing)
	{
		return;
	}
	if (Controller && amount)
	{
		FVector rght = GetActorRightVector();

		AddMovementInput(rght, amount);
	}
}

void AAvatar::moveLeft(float amount)
{
	if (inventoryShowing)
	{
		return;
	}
	if (Controller && amount)
	{
		FVector lft = -GetActorRightVector();
		
		AddMovementInput(lft, amount);
	}
}

void AAvatar::moveBack(float amount)
{
	if (inventoryShowing)
	{
		return;
	}
	if (Controller && amount)
	{
		FVector bck = -GetActorForwardVector();

		AddMovementInput(bck, amount);
	}
}

void AAvatar::yaw(float amount)
{
	if (inventoryShowing)
	{
		AMyHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AMyHUD>();
		HUD->mouseMoved();
	}
	else
	{
		AddControllerYawInput(this->sensitivity * amount * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::pitch(float amount)
{	
	if (inventoryShowing)
	{
		AMyHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AMyHUD>();
		HUD->mouseMoved();
	}
	else
	{
		AddControllerPitchInput(this->sensitivity * amount * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::toggleInventory()
{
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	AMyHUD* HUD = controller->GetHUD<AMyHUD>();

	if (inventoryShowing)
	{
		HUD->clearWidgets();
		controller->bShowMouseCursor = false;
		inventoryShowing = false;
	}
	else
	{
		inventoryShowing = true;
		controller->bShowMouseCursor = true;

		for (TMap<FString, int>::TIterator it = backpack.CreateIterator(); it; ++it)
		{
			FString title = it->Key + " x " + FString::FromInt(it->Value);
			UTexture2D* tex = icons[it->Key];

			HUD->addWidget(Widget(Icon(title, tex)));
		}
	}
}

void AAvatar::mouseClicked()
{
	AMyHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AMyHUD>();
	HUD->mouseClicked();
}

void AAvatar::pickup(APickupItem* item)
{
	if (backpack.Find(item->name))
	{
		backpack[item->name] += item->quantity;
	}
	else
	{
		backpack.Add(item->name, item->quantity);
		icons.Add(item->name, item->icon);
	}
}




