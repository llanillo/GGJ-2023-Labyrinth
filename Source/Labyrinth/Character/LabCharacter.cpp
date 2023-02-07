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

	DashForce = 300.f;
	DashCooldown = 3.f;
	bCanDash = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation({-10.f, 0.f, 60.f});
	CameraComponent->bUsePawnControlRotation = true;

	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMeshComponent"));
	FirstPersonMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	FirstPersonMeshComponent->SetupAttachment(CameraComponent);
	FirstPersonMeshComponent->SetRelativeLocation({-30.f, 0.f, -150.f});
	FirstPersonMeshComponent->bOwnerNoSee = true;

	OnTakeAnyDamage.AddUniqueDynamic(this, &ThisClass::OnCharacterReceiveDamage);
}

void ALabCharacter::BeginPlay()
{
	Super::BeginPlay();

	const FInputModeGameOnly InputModeGameOnly;

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	PlayerController->SetInputMode(InputModeGameOnly);
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
		EnhancedInputComponent->BindAction(LabPlayerController->GetInteractAction(), ETriggerEvent::Triggered, this,
		                                   &ThisClass::Interact);
	}
}

void ALabCharacter::OnDashTimeout()
{
	if (DashHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DashHandle);
	}

	bCanDash = true;
}

void ALabCharacter::OnCharacterReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                             AController* InstigatedBy, AActor* DamageCauser)
{
	ReduceTorch(Damage);
}

void ALabCharacter::Dash()
{
	if (Controller && bCanDash)
	{
		bCanDash = false;

		FVector MovementDirection = GetLastMovementInputVector();
		MovementDirection.Normalize();

		LaunchCharacter(MovementDirection * DashForce, false, false);

		GetWorldTimerManager().SetTimer(DashHandle, this, &ThisClass::OnDashTimeout, DashCooldown);
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

void ALabCharacter::Interact()
{
	if (!TorchComponent)
	{
		return;
	}

	if (FireTorchPickup)
	{
		IncreaseTorch(FireTorchPickup->GetRechargeValue());
		FireTorchPickup->Destroy();
	}
	else if (WallTorch)
	{
		const ELightStatus WallTorchStatus = WallTorch->GetWallTorchStatus();

		if (WallTorchStatus == ELightStatus::Els_On)
		{
			IncreaseTorch(100);
		}
		else if (WallTorchStatus == ELightStatus::Els_Off)
		{
			WallTorch->LightUp();
		}
	}
}

void ALabCharacter::EquipTorch(ATorch* Torch)
{
	TorchComponent = Cast<UTorchComponent>(
		AddComponentByClass(UTorchComponent::StaticClass(), false, GetActorTransform(), false));
	AddInstanceComponent(TorchComponent);

	if (TorchComponent && Torch)
	{
		TorchComponent->EquipTorch(Torch);

		BP_UpdateTorchAnimation();
	}
}

void ALabCharacter::IncreaseTorch(const int32 Value) const
{
	if (TorchComponent)
	{
		TorchComponent->IncreaseTorch(Value);
	}
}

void ALabCharacter::ResetTorch() const
{
	if (TorchComponent)
	{
		TorchComponent->ResetRemainingFire();
	}
}

void ALabCharacter::ReduceTorch(const int32 Value) const
{
	if (TorchComponent)
	{
		TorchComponent->DecreaseTorch(Value);
	}
}

void ALabCharacter::SetWallTorch(AWallTorch* NewWallTorch)
{
	ALabPlayerController* LabPlayerController = Cast<ALabPlayerController>(Controller);
	checkf(LabPlayerController, TEXT("[ALabCharacter - SetWallTorch: PlayerController is not valid]"));

	WallTorch = NewWallTorch;

	if (WallTorch)
	{
		const ULabGameInstance* LabGameInstance = GetGameInstance<ULabGameInstance>();
		checkf(LabGameInstance, TEXT("[ALabCharacter - SetWallTorch: GameInstance is not valid]"));

		const FString ShowMessage = NewWallTorch->GetWallTorchStatus() == ELightStatus::Els_On
			                            ? LabGameInstance->GetWallTorchRechargeMessage()
			                            : LabGameInstance->GetWallTorchLightUpMessage();
		LabPlayerController->ShowMessageHUD(ShowMessage);
	}
	else
	{
		LabPlayerController->HideMessageHUD();
	}
}

void ALabCharacter::SetPickup(AFireTorchPickup* TorchPickup)
{
	ALabPlayerController* LabPlayerController = Cast<ALabPlayerController>(Controller);
	checkf(LabPlayerController, TEXT("[ALabCharacter - SetPickup: PlayerController is not valid]"));

	FireTorchPickup = TorchPickup;

	if (TorchComponent && FireTorchPickup)
	{
		LabPlayerController->ShowMessageHUD("[E] - Pick up to recharge torch");
	}
	else
	{
		LabPlayerController->HideMessageHUD();
	}
}
