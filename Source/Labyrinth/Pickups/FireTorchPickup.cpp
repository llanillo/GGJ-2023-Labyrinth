#include "FireTorchPickup.h"

#include "GameFramework/Character.h"
#include "Labyrinth/Character/LabCharacter.h"

AFireTorchPickup::AFireTorchPickup(): Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFireTorchPickup::OnCharacterBeginOverlap(ACharacter* CharacterWhoPickup)
{
	Super::OnCharacterBeginOverlap(CharacterWhoPickup);

	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(CharacterWhoPickup))
	{
		LabCharacter->SetPickup(this);
	}
}

void AFireTorchPickup::OnCharacterEndOverlap(ACharacter* CharacterWhoPickup)
{
	Super::OnCharacterEndOverlap(CharacterWhoPickup);

	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(CharacterWhoPickup))
	{
		LabCharacter->SetPickup(nullptr);
	}
}
