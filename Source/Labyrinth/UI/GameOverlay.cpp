#include "GameOverlay.h"

#include "Components/TextBlock.h"

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

void UGameOverlay::SetMessage(const FText& NewText) const
{
	if(MessageTextBlock)
	{
		MessageTextBlock->SetText(NewText);
	}
}
