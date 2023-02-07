// Fill out your copyright notice in the Description page of Project Settings.
#include "MenuOverlay.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Labyrinth/Core/LabGameInstance.h"
#include "Labyrinth/UI/CreditsOverlay.h"

bool UMenuOverlay::Initialize()
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

void UMenuOverlay::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMenuOverlay::OnStartButtonClicked()
{
	if (const ULabGameInstance* LabGameInstance = GetGameInstance<ULabGameInstance>())
	{
		UGameplayStatics::OpenLevel(this, LabGameInstance->GetPrincipalLevelName());
	}
}

void UMenuOverlay::OnCreditsButtonClicked()
{
	OnCreditsClicked.Broadcast();
}

void UMenuOverlay::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
