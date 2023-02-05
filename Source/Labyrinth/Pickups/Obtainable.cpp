#include "Obtainable.h"

#include "Labyrinth/Character/LabCharacter.h"
#include "Labyrinth/Components/PickupComponent.h"

AObtainable::AObtainable()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootSceneComponent;

	TorchNMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorchMeshComponent"));
	TorchNMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	TorchNMeshComponent->SetupAttachment(RootComponent);

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupComponent"));
	PickupComponent->SetupAttachment(RootComponent);
	PickupComponent->OnCharacterBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnPickup);
}

void AObtainable::BeginPlay()
{
	Super::BeginPlay();
}

void AObtainable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObtainable::OnPickup(ACharacter* CharacterWhoPickup)
{
}
