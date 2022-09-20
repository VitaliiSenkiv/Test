// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
class Icon
{
public:
	FString m_name;
	UTexture2D* m_texture;

	Icon(FString& name, UTexture2D* texture)
		: m_name(name), m_texture(texture)
	{}
	Icon(): m_name("unnamed"), m_texture(nullptr) 
	{}
};

class Widget
{
public:
	FVector2D m_pos, m_size;
	Icon m_icon;

	Widget(Icon icon): m_icon(icon)
	{}

	float left() { return m_pos.X; }
	float right() { return m_pos.X + m_size.X; }
	float top() { return m_pos.Y; }
	float bottom() { return m_pos.Y + m_size.Y; }
	float width() { return m_size.X; }
	float height() { return m_size.Y; }

	bool isHited(FVector2D point)
	{
		return point.X > left() && point.X < right() && point.Y > top() && point.Y < bottom();
	}
};

class Message
{
public:

	FString m_message;
	float m_time;
	FColor m_color;
	bool m_isRainbow;
	UTexture2D* m_face;

	Message(FString message, float time, FColor color, UTexture2D* face, bool isRainbow = false) :
		m_message(message), m_time(time), m_color(color), m_face(face), m_isRainbow(isRainbow)
	{}
	//Message() : Message("None", 5.f, FColor::White) {}
};

UCLASS()
class TEST_API AMyHUD : public AHUD
{
	GENERATED_BODY()

	TArray<Widget> widgets;

	Widget* heldWidget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* HUDfont;

	FVector2D dims;

	TArray<Message> messages;

	AMyHUD(){}

	virtual void DrawHUD() override;

	void drawMessages(int canvasW, int canvasH);
	void drawHealthbar(int canvasW, int canvasH);
	void drawWidgets();

	void addMessage(Message msg);
	void addWidget(Widget widget);

	void clearWidgets();

	void mouseClicked();
	void mouseMoved();
};
