#include "LabHUD.h"

#include "EventOverlay.h"
#include "Blueprint/UserWidget.h"
#include "Labyrinth/UI/GameOverlay.h"

ALabHUD::ALabHUD()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALabHUD::BeginPlay()
{
	Super::BeginPlay();
	checkf(GameOverlayClass, TEXT("[ALabHUD - BeginPlay: GameOverlayClass is not valid]"));
	checkf(EventOverlayClass, TEXT("[ALabHUD - BeginPlay: EventOverlayClass is not valid]"));

	GameOverlay = CreateWidget<UGameOverlay>(GetOwningPlayerController(), GameOverlayClass);
	EventOverlay = CreateWidget<UEventOverlay>(GetOwningPlayerController(), EventOverlayClass);
	checkf(GameOverlay, TEXT("[ALabHUD - BeginPlay: GameOverlay is not valid]"));
	checkf(GameOverlay, TEXT("[ALabHUD - BeginPlay: EventOverlay is not valid]"));

	GameOverlay->AddToViewport();
	EventOverlay->AddToViewport();
}

void ALabHUD::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabHUD::HideMessage() const
{
	if (GameOverlay)
	{
		GameOverlay->HideMessage();
	}
}

void ALabHUD::ShowJumpScare() const
{
	if (EventOverlay)
	{
		EventOverlay->StartJumpScareAnimation();
	}
}

void ALabHUD::ShowDamageIndicator() const
{
	if (EventOverlay)
	{
		EventOverlay->StartDamageIndicatorAnimation();
	}
}

void ALabHUD::ShowGameOver() const
{
	if (GameOverlay)
	{
		GameOverlay->ShowGameOver();
	}
}

void ALabHUD::ShowCentralScreenMessage(const FString& Message) const
{
	if (GameOverlay)
	{
		const FText MessageText = FText::FromString(Message);
		GameOverlay->SetMessage(MessageText);
	}
}

void ALabHUD::ShowRemainingTorch(const int32 RemainingTorch) const
{
	if (GameOverlay)
	{
		if (RemainingTorch > 0)
		{
			const FText TorchText = FText::FromString(FString::FromInt(RemainingTorch));
			GameOverlay->SetRemainingFire(TorchText);
		}
		else
		{
			GameOverlay->HideRemainingFire();
		}
	}
}