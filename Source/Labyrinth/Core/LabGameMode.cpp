#include "LabGameMode.h"

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
	// TODO
}

