#include "GameOverlay.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

bool UGameOverlay::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (MessageTextBlock)
	{
		MessageTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}

	if (RemainingTorchTextBlock)
	{
		RemainingTorchTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameOverText)
	{
		GameOverText->SetVisibility(ESlateVisibility::Hidden);
	}

	return true;
}


void UGameOverlay::ShowGameOver() const
{
	GameOverText->SetVisibility(ESlateVisibility::Visible);
}

void UGameOverlay::SetRemainingTorchText(const FText& NewText) const
{
	if (RemainingTorchTextBlock)
	{
		RemainingTorchTextBlock->SetVisibility(ESlateVisibility::Visible);
		RemainingTorchTextBlock->SetText(NewText);
	}
}

void UGameOverlay::SetMessage(const FText& NewText) const
{
	if (MessageTextBlock)
	{
		MessageTextBlock->SetVisibility(ESlateVisibility::Visible);
		MessageTextBlock->SetText(NewText);
	}
}

void UGameOverlay::HideMessage() const
{
	MessageTextBlock->SetVisibility(ESlateVisibility::Hidden);
}