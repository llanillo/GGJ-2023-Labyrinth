#include "Torch.h"

#include "Labyrinth/Character/LabCharacter.h"
#include "Labyrinth/Components/PickupComponent.h"

ATorch::ATorch()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupComponent"));
	PickupComponent->SetupAttachment(RootComponent);
	PickupComponent->OnPickupEvent.AddUniqueDynamic(this, &ThisClass::OnPickup);
}

void ATorch::BeginPlay()
{
	Super::BeginPlay();
}

void ATorch::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATorch::OnPickup(ACharacter* CharacterWhoPickup)
{
	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(CharacterWhoPickup))
	{
		LabCharacter->EquipTorch(this);
	}
}
