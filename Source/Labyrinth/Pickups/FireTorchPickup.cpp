#include "FireTorchPickup.h"

#include "GameFramework/Character.h"
#include "Labyrinth/Character/LabCharacter.h"

AFireTorchPickup::AFireTorchPickup()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFireTorchPickup::OnPickup(ACharacter* CharacterWhoPickup)
{
	if (const ALabCharacter* LabCharacter = Cast<ALabCharacter>(CharacterWhoPickup))
	{
		LabCharacter->IncreaseTorch(RechargeValue);
	}
}