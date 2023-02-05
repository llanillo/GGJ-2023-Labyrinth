#include "Torch.h"

#include "Components/StaticMeshComponent.h"
#include "Labyrinth/Character/LabCharacter.h"
#include "Niagara/Public/NiagaraComponent.h"

ATorch::ATorch() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentFireLevel = EFireLevel::Efl_High;
}

void ATorch::BeginPlay()
{
	Super::BeginPlay();
}

void ATorch::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATorch::SetFireLevel(EFireLevel FireLevel)
{
	if (UNiagaraComponent* FireNiagaraComponent = GetFireParticleSystem())
	{
		CurrentFireLevel = FireLevel;

		switch (CurrentFireLevel)
		{
		// TODO: Agregar animaciones?¿?
		case EFireLevel::Efl_Low:
			FireNiagaraComponent->SetFloatParameter("", 1.f);
			break;
		case EFireLevel::Efl_Half:
			FireNiagaraComponent->SetFloatParameter("", 1.f);
			break;
		case EFireLevel::Efl_High:
			FireNiagaraComponent->SetFloatParameter("", 1.f);
			break;
		default: ;
			UE_LOG(LogTemp, Error, TEXT("[ATorch - SetFireLevel: FireLevel is not valid]"));
			break;
		}
	}
}

void ATorch::OnPickup(ACharacter* CharacterWhoPickup)
{
	Super::OnPickup(CharacterWhoPickup);
	
	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(CharacterWhoPickup))
	{
		LabCharacter->EquipTorch(this);
	}
}
