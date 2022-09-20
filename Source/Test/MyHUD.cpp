// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "Avatar.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"


void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	dims.X = Canvas->SizeX;
	dims.Y = Canvas->SizeY;

	drawMessages(Canvas->SizeX, Canvas->SizeY);
	drawHealthbar(Canvas->SizeX, Canvas->SizeY);
	drawWidgets();
}

void AMyHUD::drawMessages(int canvasW, int canvasH)
{
	for (int i = messages.Num() - 1; i >= 0; --i)
	{
		float textWidth, textHeight, pad = 10.f;
		GetTextSize(messages[i].m_message, textWidth, textHeight, HUDfont);

		float messageH = textHeight + 2 * pad;
		float X = 0, Y = i * messageH;

		DrawRect(FLinearColor(0, 0, 0, 0.25), X, Y, canvasW, messageH);

		DrawTexture(messages[i].m_face, X, Y, messageH, messageH, 0, 0, 1, 1);

		DrawText(messages[i].m_message,
			messages[i].m_isRainbow? FColor::MakeRandomColor() :messages[i].m_color, X + pad + messageH, Y+pad,
			HUDfont, 1.3);

		messages[i].m_time -= GetWorld()->GetDeltaSeconds();

		if (messages[i].m_time < 0)
		{
			messages.RemoveAt(i);
		}
	}
}

void AMyHUD::drawHealthbar(int canvasW, int canvasH)
{
	AAvatar* player = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	float barWidth = canvasW/3, barHeight = canvasH/20, pad = 10;

	float X = (canvasW - barWidth) / 2;
	float Y = canvasH - barHeight - pad;

	float percHP = static_cast<float>(player->currentHP) / player->maxHP;

	DrawRect(FLinearColor(0.7, 0.7, 0.7, 0.5), X, Y, barWidth, barHeight);
	DrawRect(FLinearColor(1 - percHP, percHP, 0), X, Y, barWidth * percHP, barHeight);

	DrawText(FString::FromInt(player->currentHP) + '/' + FString::FromInt(player->maxHP), 
		FColor::Black, X, Y, HUDfont, 2);
}

void AMyHUD::drawWidgets()
{
	AAvatar* player = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (player->inventoryShowing)
	{
		DrawRect(FLinearColor(0.7, 0.7, 0.7, 0.5), 0, 0, dims.X, dims.Y);
		DrawText("Inventory", FLinearColor::White, 100, 20, HUDfont, 1.5);
	}

	for (int i = 0; i < widgets.Num(); ++i)
	{
		DrawTexture(widgets[i].m_icon.m_texture, widgets[i].left(), widgets[i].top(),
			widgets[i].width(), widgets[i].height(), 0, 0, 1, 1);
		DrawText(widgets[i].m_icon.m_name, FColor::MakeRandomColor(), widgets[i].left(),
			widgets[i].top(), HUDfont);
	}
}

void AMyHUD::addMessage(Message msg)
{
	messages.Add(msg);
}

void AMyHUD::addWidget(Widget widget)
{
	FVector2D start(100, 100), pad(12, 12);
	widget.m_size = FVector2D(100, 100);

	widget.m_pos = start;

	for (int i = 0; i < widgets.Num(); ++i)
	{
		widget.m_pos.X += widget.m_size.X + pad.X;

		if (widget.m_pos.X + widget.m_size.X > dims.X)
		{
			widget.m_pos.X = start.X;
			widget.m_pos.Y += widget.m_size.Y + pad.Y;
		}
	}

	widgets.Add(widget);
}

void AMyHUD::clearWidgets()
{
	widgets.Empty();
}

void AMyHUD::mouseClicked()
{
	APlayerController* pController = GetWorld()->GetFirstPlayerController();

	FVector2D mousePos;
	pController->GetMousePosition(mousePos.X, mousePos.Y);

	heldWidget = nullptr;

	for (int i = 0; i < widgets.Num(); ++i)
	{
		if (widgets[i].isHited(mousePos))
		{
			heldWidget = &(widgets[i]);
			return;
		}
	}
}

void AMyHUD::mouseMoved()
{
	static FVector2D lastMousePos;
	FVector2D currentMousePos, mouseShift;

	APlayerController* pController = GetWorld()->GetFirstPlayerController();
	pController->GetMousePosition(currentMousePos.X, currentMousePos.Y);

	mouseShift = currentMousePos - lastMousePos;

	float pressTime = pController->GetInputKeyTimeDown(EKeys::LeftMouseButton);


	if (pressTime > 0.0f && heldWidget)
	{
		heldWidget->m_pos += mouseShift;
	}

	lastMousePos = currentMousePos;
}
