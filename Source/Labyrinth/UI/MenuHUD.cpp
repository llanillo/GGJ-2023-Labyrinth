#include "MenuHUD.h"

#include "MenuOverlay.h"
#include "CreditsOverlay.h"

AMenuHUD::AMenuHUD()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	checkf(MenuOverlayClass, TEXT("[AMenuHUD - BeginPlay: MenuOverlayClass is not valid]"));
	checkf(CreditsOverlayClass, TEXT("[AMenuHUD - BeginPlay: CreditsOverlayClass is not valid]"));

	const FInputModeUIOnly InputModeUIOnly;
	APlayerController* CurrentOwner = Cast<APlayerController>(GetOwner());
	CurrentOwner->bShowMouseCursor = true;
	CurrentOwner->SetInputMode(InputModeUIOnly);

	MenuOverlay = CreateWidget<UMenuOverlay>(CurrentOwner, MenuOverlayClass);
	CreditsOverlay = CreateWidget<UCreditsOverlay>(CurrentOwner, CreditsOverlayClass);

	MenuOverlay->OnCreditsClicked.AddUniqueDynamic(this, &ThisClass::ShowCreditsOverlay);
	CreditsOverlay->OnBackClicked.AddUniqueDynamic(this, &ThisClass::ShowMainMenuOverlay);

	MenuOverlay->AddToViewport();
}

void AMenuHUD::ShowMainMenuOverlay()
{
	if (CreditsOverlay)
	{
		CreditsOverlay->RemoveFromParent();
	}

	if (MenuOverlay)
	{
		MenuOverlay->AddToViewport();
	}
}

void AMenuHUD::ShowCreditsOverlay()
{
	if (MenuOverlay)
	{
		MenuOverlay->RemoveFromParent();
	}

	if (CreditsOverlay)
	{
		CreditsOverlay->AddToViewport();
	}
}
