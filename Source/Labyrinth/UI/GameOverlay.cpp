#include "GameOverlay.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"

void UGameOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	MessageTextBlock->SetVisibility(ESlateVisibility::Hidden);
	RemainingTorchTextBlock->SetVisibility(ESlateVisibility::Hidden);
}

void UGameOverlay::StartDamageIndicatorAnimation()
{
	if (!IsAnimationPlaying(DamageIndicatorAnim))
	{
		PlayAnimation(DamageIndicatorAnim, 0.f);
	}
}

void UGameOverlay::OnFinishedDamageIndicatorAnimation()
{
	PlayAnimationReverse(DamageIndicatorAnim);
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
