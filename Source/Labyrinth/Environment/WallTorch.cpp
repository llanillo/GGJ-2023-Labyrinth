#include "WallTorch.h"
#include "Labyrinth/Components/PickupComponent.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Labyrinth/Character/LabCharacter.h"

AWallTorch::AWallTorch()
{
	PrimaryActorTick.bCanEverTick = true;

	FireNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	FireNiagaraComponent->SetupAttachment(RootComponent);
	FireNiagaraComponent->Deactivate();

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("SphereComponent"));
	PickupComponent->OnCharacterBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnWallTorchBeginOverlap);
	PickupComponent->OnCharacterBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnWallTorchBeginOverlap);
}

void AWallTorch::BeginPlay()
{
	Super::BeginPlay();
}

void AWallTorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWallTorch::LightUp()
{
	CurrentLightStatus = ELightStatus::Els_On;
	FireNiagaraComponent->Activate();
}

void AWallTorch::RechargeTorch()
{
	if (CurrentLightStatus != ELightStatus::Els_On)
	{
		return;
	}
}

void AWallTorch::OnWallTorchBeginOverlap(ACharacter* CharacterWhoPickup)
{
	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(CharacterWhoPickup))
	{
		LabCharacter->SetLastWallTorch(this);
	}
}

void AWallTorch::OnWallTorchEndOverlap(ACharacter* CharacterWhoPickup)
{
	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(CharacterWhoPickup))
	{
		LabCharacter->SetLastWallTorch(nullptr);
	}
}
