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
	PickupComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PickupComponent->OnCharacterBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCharacterBeginOverlap);
	PickupComponent->OnCharacterEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCharacterEndOverlap);
	PickupComponent->SetupAttachment(RootComponent);
}

void AObtainable::BeginPlay()
{
	Super::BeginPlay();
}

void AObtainable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObtainable::OnCharacterBeginOverlap(ACharacter* CharacterWhoPickup)
{
}

void AObtainable::OnCharacterEndOverlap(ACharacter* CharacterWhoPickup)
{
}
