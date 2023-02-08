#include "EventOverlay.h"

#include "Components/Border.h"
#include "Components/Image.h"

bool UEventOverlay::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (DamageIndicatorImage)
	{
		DamageIndicatorImage->SetVisibility(ESlateVisibility::Hidden);
	}

	if (JumpScareBorder)
	{
		JumpScareBorder->SetVisibility(ESlateVisibility::Hidden);
	}

	if (JumpScareAnim)
	{
		FWidgetAnimationDynamicEvent AnimationDynamicEvent;
		AnimationDynamicEvent.BindDynamic(this, &ThisClass::OnJumpScareAnimFinished);
		BindToAnimationFinished(JumpScareAnim, AnimationDynamicEvent);
	}

	return true;
}

void UEventOverlay::OnJumpScareAnimFinished()
{
	JumpScareBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UEventOverlay::StartDamageIndicatorAnimation()
{
	if (!IsAnimationPlaying(DamageIndicatorAnim))
	{
		DamageIndicatorImage->SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(DamageIndicatorAnim, 0.f);
	}
}

void UEventOverlay::StartJumpScareAnimation()
{
	if (!IsAnimationPlaying(JumpScareAnim))
	{
		JumpScareBorder->SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(JumpScareAnim);
	}
}