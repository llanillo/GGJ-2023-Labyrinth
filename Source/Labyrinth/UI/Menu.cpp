// Fill out your copyright notice in the Description page of Project Settings.
#include "Menu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Labyrinth/Core/LabGameInstance.h"
#include "Labyrinth/UI/CreditsOverlay.h"

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (StartButton)
	{
		StartButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnStartButtonClicked);
	}

	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnCreditsButtonClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnQuitButtonClicked);
	}

	return true;
}

void UMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if(CreditsOverlayClass)
	{
		CreditsOverlay = CreateWidget<UCreditsOverlay>(GetOwningPlayer(), CreditsOverlayClass);
	}
}

void UMenu::OnStartButtonClicked()
{
	if (const ULabGameInstance* LabGameInstance = GetGameInstance<ULabGameInstance>())
	{
		UGameplayStatics::OpenLevel(this, LabGameInstance->GetLabLevelName());
	}
}

void UMenu::OnCreditsButtonClicked()
{
}

void UMenu::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
