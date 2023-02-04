#include "LabGameMode.h"

#include "LabGameInstance.h"
#include "Kismet/GameplayStatics.h"

ALabGameMode::ALabGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALabGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ALabGameMode::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabGameMode::GameOver()
{
	if (ULabGameInstance* LabGameInstance = GetGameInstance<ULabGameInstance>())
	{
		UGameplayStatics::OpenLevel(this, LabGameInstance->GetMainMenuLevelName(), true);
	}
}
