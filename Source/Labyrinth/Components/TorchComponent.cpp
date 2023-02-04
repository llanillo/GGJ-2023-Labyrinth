#include "TorchComponent.h"

#include "Labyrinth/Core/LabGameMode.h"

UTorchComponent::UTorchComponent()
{
	MaximumFire = 100.f;

	RemainingFire = MaximumFire;
}

void UTorchComponent::BeginPlay()
{
	Super::BeginPlay();

	/* Start torch timer to decrease it "DecreaseAmount" each second */
	FTimerDelegate TorchDecreaseDelegate;
	TorchDecreaseDelegate.BindUObject(this, &ThisClass::DecreaseTorch, DecreaseAmount);

	GetWorld()->GetTimerManager().SetTimer(DecreaseTorchHandle, TorchDecreaseDelegate, 1.f, true);
}

void UTorchComponent::IncreaseTorch(const float Value)
{
	RemainingFire = FMath::Clamp(RemainingFire + Value, 0.f, MaximumFire);
}

void UTorchComponent::DecreaseTorch(const float Value)
{
	RemainingFire -= Value;

	if(RemainingFire > 0.f)
	{
		return;
	}

	if(ALabGameMode* LabGameMode = GetWorld()->GetAuthGameMode<ALabGameMode>())
	{
		LabGameMode->GameOver();
	}
	
}