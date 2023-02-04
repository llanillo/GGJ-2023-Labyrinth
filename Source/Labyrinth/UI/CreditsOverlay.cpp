#include "CreditsOverlay.h"

#include "Components/Button.h"

bool UCreditsOverlay::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	if(BackButton)
	{
		BackButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnBackButtonClicked);
	}

	return true;
}

void UCreditsOverlay::OnBackButtonClicked()
{
	RemoveFromParent();
}
