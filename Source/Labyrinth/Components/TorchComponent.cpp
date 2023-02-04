#include "TorchComponent.h"

#include "Labyrinth/Core/LabGameMode.h"

UTorchComponent::UTorchComponent()
{
	MaxTorch = 100.f;

	RemainingTorch = MaxTorch;
}

void UTorchComponent::DecreaseTorch(const float Value)
{
	RemainingTorch -= Value;

	if(RemainingTorch > 0.f)
	{
		return;
	}

	if(ALabGameMode* LabGameMode = GetWorld()->GetAuthGameMode<ALabGameMode>())
	{
		LabGameMode->GameOver();
	}
	
}
