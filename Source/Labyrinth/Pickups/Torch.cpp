#include "Torch.h"

#include "Components/StaticMeshComponent.h"
#include "Labyrinth/Character/LabCharacter.h"
#include "Labyrinth/Components/PickupComponent.h"
#include "Niagara/Public/NiagaraComponent.h"

ATorch::ATorch()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentFireLevel = EFireLevel::Efl_High;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootSceneComponent;

	TorchNMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorchMeshComponent"));
	TorchNMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	TorchNMeshComponent->SetupAttachment(RootComponent);

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupComponent"));
	PickupComponent->SetupAttachment(RootComponent);
	PickupComponent->OnCharacterBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnPickup);
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

void ATorch::SetFireLevel(EFireLevel FireLevel)
{
	if (FireParticlesSystem)
	{
		CurrentFireLevel = FireLevel;

		switch (CurrentFireLevel)
		{
			// TODO: Agregar animaciones?¿?
		case EFireLevel::Efl_Low:
			FireParticlesSystem->SetFloatParameter("", 1.f);
			break;
		case EFireLevel::Efl_Half:
			FireParticlesSystem->SetFloatParameter("", 1.f);
			break;
		case EFireLevel::Efl_High:
			FireParticlesSystem->SetFloatParameter("", 1.f);
			break;
		default: ;
			UE_LOG(LogTemp, Error, TEXT("[ATorch - SetFireLevel: FireLevel is not valid]"));
			break;
		}
	}
}
