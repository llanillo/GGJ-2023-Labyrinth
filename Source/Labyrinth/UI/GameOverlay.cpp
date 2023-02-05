#include "GameOverlay.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

bool UGameOverlay::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (DamageIndicatorImage)
	{
		DamageIndicatorImage->SetVisibility(ESlateVisibility::Hidden);
	}

	if (JumpScareImage)
	{
		JumpScareImage->SetVisibility(ESlateVisibility::Hidden);
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

	if (JumpScareAnim)
	{
		FWidgetAnimationDynamicEvent AnimationDynamicEvent;
		AnimationDynamicEvent.BindDynamic(this, &ThisClass::OnJumpScareAnimFinished);
		BindToAnimationFinished(JumpScareAnim, AnimationDynamicEvent);
	}

	return true;
}

void UGameOverlay::OnDamageIndicatorAnimFinished()
{
	DamageIndicatorImage->SetVisibility(ESlateVisibility::Hidden);
	PlayAnimationReverse(DamageIndicatorAnim);
}

void UGameOverlay::OnJumpScareAnimFinished()
{
	JumpScareImage->SetVisibility(ESlateVisibility::Hidden);
}

void UGameOverlay::StartDamageIndicatorAnimation()
{
	if (!IsAnimationPlaying(DamageIndicatorAnim))
	{
		DamageIndicatorImage->SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(DamageIndicatorAnim, 0.f);
	}
}

void UGameOverlay::StartJumpScareAnimation()
{
	if (!IsAnimationPlaying(JumpScareAnim))
	{
		JumpScareImage->SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(JumpScareAnim);
	}
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
