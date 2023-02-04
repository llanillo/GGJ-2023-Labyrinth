﻿#include "FireTorchPickup.h"

#include "GameFramework/Character.h"
#include "Labyrinth/Character/LabCharacter.h"
#include "Labyrinth/Components/PickupComponent.h"

AFireTorchPickup::AFireTorchPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupComponent"));
	PickupComponent->SetupAttachment(RootComponent);
	// PickupComponent->OnPickupEvent.AddUniqueDynamic(this, &ThisClass::OnPickUp);
}

void AFireTorchPickup::OnPickUp(ACharacter* CharacterWhoPickup)
{
	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(CharacterWhoPickup))
	{
		LabCharacter->IncreaseTorch(RechargeValue);
	}
}