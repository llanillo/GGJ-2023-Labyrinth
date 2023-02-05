#include "TorchComponent.h"

#include "Labyrinth/Character/LabCharacter.h"
#include "Labyrinth/Core/LabGameMode.h"
#include "Labyrinth/Pickups/Torch.h"
#include "Labyrinth/Player/LabPlayerController.h"

UTorchComponent::UTorchComponent()
{
	MaximumFire = 100;

	RemainingFire = MaximumFire;
	DecreaseAmount = 1;
	bCanIncreaseTorch = true;
	IncreaseTorchCooldown = 3;
}

void UTorchComponent::BeginPlay()
{
	Super::BeginPlay();

	/* Start torch timer to decrease it "DecreaseAmount" each second */
	FTimerDelegate TorchDecreaseDelegate;
	TorchDecreaseDelegate.BindUObject(this, &ThisClass::DecreaseTorch, DecreaseAmount);

	GetWorld()->GetTimerManager().SetTimer(DecreaseTorchHandle, TorchDecreaseDelegate, 1.f, true);
}

void UTorchComponent::IncreaseTorch(const int32 Value)
{
	if (bCanIncreaseTorch)
	{
		RemainingFire = FMath::Clamp(RemainingFire + Value, 0, MaximumFire);
		bCanIncreaseTorch = false;

		GetWorld()->GetTimerManager().SetTimer(IncreaseTorchHandle, this, &ThisClass::OnIncreaseTorchTimeout,
		                                       IncreaseTorchCooldown, false);
	}
}

void UTorchComponent::OnIncreaseTorchTimeout()
{
	//BUG?
	//Aqui se elimina el timer de decrease, esto no esta mal?
	//Se puede usar pause y unpause si la idea es detenerlo un momento...
	if(DecreaseTorchHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(DecreaseTorchHandle);
	}
	
	bCanIncreaseTorch = true;
}

void UTorchComponent::DecreaseTorch(const int32 Value)
{
	RemainingFire -= Value;

	const ACharacter* OwnerCharacter = GetOwner<ACharacter>();
	checkf(OwnerCharacter, TEXT("[UTorchComponent - DecreaseTorch: Character is not valid]"));

	const ALabPlayerController* LabPlayerController = Cast<ALabPlayerController>(OwnerCharacter->Controller);
	checkf(LabPlayerController, TEXT("[UTorchComponent - DecreaseTorch: PlayerController is not valid]"));

	LabPlayerController->ShowRemainingTorch(FString::FromInt(RemainingFire));

	if (RemainingFire > 0.f)
	{
		return;
	}

	if (const ALabGameMode* LabGameMode = GetWorld()->GetAuthGameMode<ALabGameMode>())
	{
		LabGameMode->GameOver();
	}
}

void UTorchComponent::EquipTorch(ATorch* NewTorch)
{
	if (!NewTorch)
	{
		return;
	}

	if (const ALabCharacter* OwnerPawn = Cast<ALabCharacter>(GetOwner()))
	{
		Torch = NewTorch;
		Torch->SetOwner(GetOwner());

		const FAttachmentTransformRules AttachmentTransformRules =
			FAttachmentTransformRules::SnapToTargetIncludingScale;
		Torch->AttachToComponent(OwnerPawn->GetFirstPersonMesh(), AttachmentTransformRules, "GripPoint");
	}
}
