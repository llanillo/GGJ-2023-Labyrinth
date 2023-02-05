#include "LabCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Labyrinth/Components/TorchComponent.h"
#include "Labyrinth/Core/LabGameInstance.h"
#include "Labyrinth/Environment/WallTorch.h"
#include "Labyrinth/Pickups/FireTorchPickup.h"
#include "Labyrinth/Pickups/Torch.h"
#include "Labyrinth/Player/LabPlayerController.h"


ALabCharacter::ALabCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	DashForce = 50.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation({-10.f, 0.f, 60.f});
	CameraComponent->bUsePawnControlRotation = true;

	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMeshComponent"));
	FirstPersonMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // TODO: Cambiar¿?¿
	FirstPersonMeshComponent->SetupAttachment(CameraComponent);
	FirstPersonMeshComponent->SetRelativeLocation({-30.f, 0.f, -150.f});

}

void ALabCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALabCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const ALabPlayerController* LabPlayerController = Cast<ALabPlayerController>(Controller);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (LabPlayerController && EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(LabPlayerController->GetMoveAction(), ETriggerEvent::Triggered, this,
		                                   &ThisClass::Move);
		EnhancedInputComponent->BindAction(LabPlayerController->GetLookAction(), ETriggerEvent::Triggered, this,
		                                   &ThisClass::Look);
		EnhancedInputComponent->BindAction(LabPlayerController->GetJumpAction(), ETriggerEvent::Triggered, this,
		                                   &ThisClass::Jump);
		EnhancedInputComponent->BindAction(LabPlayerController->GetDashAction(), ETriggerEvent::Triggered, this,
		                                   &ThisClass::Dash);
		EnhancedInputComponent->BindAction(LabPlayerController->GetCrouchAction(), ETriggerEvent::Triggered, this,
		                                   &ACharacter::Crouch, false);
		EnhancedInputComponent->BindAction(LabPlayerController->GetCrouchAction(), ETriggerEvent::Completed, this,
		                                   &ACharacter::UnCrouch, false);
		EnhancedInputComponent->BindAction(LabPlayerController->GetPickupAction(), ETriggerEvent::Triggered, this,
		                                   &ThisClass::Pickup);
	}
}

void ALabCharacter::Dash()
{
	if (Controller)
	{
		LaunchCharacter(GetActorForwardVector() * DashForce, true, false);
	}
}

void ALabCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ALabCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void ALabCharacter::Pickup()
{
	if (FireTorchPickup && TorchComponent)
	{
		IncreaseTorch(FireTorchPickup->GetRechargeValue());
	}
}

void ALabCharacter::EquipTorch(ATorch* Torch)
{
	TorchComponent = NewObject<UTorchComponent>(this, UTorchComponent::StaticClass(), TEXT("TorchComponent"));

	if (TorchComponent && Torch)
	{
		AddComponentByClass(UTorchComponent::StaticClass(), false, GetActorTransform(), false);
		TorchComponent->EquipTorch(Torch);
	}
}

void ALabCharacter::IncreaseTorch(const float Value) const
{
	if (TorchComponent)
	{
		TorchComponent->IncreaseTorch(Value);
	}
}

void ALabCharacter::ReduceTorch(const float Value) const
{
	if (TorchComponent)
	{
		TorchComponent->DecreaseTorch(Value);
	}
}

void ALabCharacter::SetWallTorch(AWallTorch* WallTorch)
{
	const ALabPlayerController* LabPlayerController = Cast<ALabPlayerController>(Controller);
	checkf(LabPlayerController, TEXT("[ALabCharacter - SetLastWallTorch: PlayerController is not valid]"));

	if (WallTorch)
	{
		const ULabGameInstance* LabGameInstance = GetGameInstance<ULabGameInstance>();
		checkf(LabGameInstance, TEXT("[ALabCharacter - SetLastWallTorch: GameInstance is not valid]"));

		if (WallTorch->GetWallTorchStatus() == ELightStatus::Els_On)
		{
			LastWallTorch = WallTorch;
			LabPlayerController->ShowMessageHUD(LabGameInstance->GetWallTorchRechargeMessage());
		}
		else
		{
			LastWallTorch = WallTorch;
			LabPlayerController->ShowMessageHUD(LabGameInstance->GetWallTorchLightUpMessage());
		}
	}
	else
	{
		LastWallTorch = nullptr;
		LabPlayerController->HideMessageHUD();
	}
}

void ALabCharacter::SetPickup(AFireTorchPickup* TorchPickup)
{
	const ALabPlayerController* LabPlayerController = Cast<ALabPlayerController>(Controller);
	checkf(LabPlayerController, TEXT("[ALabCharacter - SetPickup: PlayerController is not valid]"));

	if (TorchPickup)
	{
		FireTorchPickup = TorchPickup;
		LabPlayerController->ShowMessageHUD("Pick up to recharge torch");
	}
	else
	{
		FireTorchPickup = nullptr;
		LabPlayerController->HideMessageHUD();
	}
}