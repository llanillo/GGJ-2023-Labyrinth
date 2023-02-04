#include "GameOverlay.h"

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
