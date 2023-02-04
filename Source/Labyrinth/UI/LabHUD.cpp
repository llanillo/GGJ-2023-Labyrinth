﻿#include "LabHUD.h"

#include "Blueprint/UserWidget.h"
#include "Labyrinth/UI/GameOverlay.h"

ALabHUD::ALabHUD()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned

void ALabHUD::BeginPlay()
{
	Super::BeginPlay();
	checkf(GameOverlayClass, TEXT("[ALabHUD - BeginPlay: GameOverlayClass is not valid]"));

	GameOverlay = CreateWidget<UGameOverlay>(GetOwner(), GameOverlayClass);
	checkf(GameOverlay, TEXT("[ALabHUD - BeginPlay: GameOverlay is not valid]"));

	GameOverlay->AddToViewport();
}

void ALabHUD::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabHUD::ShowInitialStory()
{
}


void ALabHUD::SetGameMessage(const FString& Message) const
{
	if (GameOverlay)
	{
		const FText MessageText = FText::FromString(Message);
		GameOverlay->SetMessage(MessageText);
	}
}
