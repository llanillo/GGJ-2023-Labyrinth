#include "Goblin.h"

AGoblin::AGoblin()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGoblin::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGoblin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGoblin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

