#include "LabCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Labyrinth/Components/TorchComponent.h"
#include "Labyrinth/Pickups/FireTorchPickup.h"
#include "Labyrinth/Pickups/Torch.h"
#include "Labyrinth/Player/LabPlayerController.h"


ALabCharacter::ALabCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	DashForce = 50.f;

	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMeshComponent"));
	FirstPersonMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // TODO: Cambiar¿?¿
	FirstPersonMeshComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);

	// TorchComponent = CreateDefaultSubobject<UTorchComponent>(TEXT("TorchComponent"));
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

void ALabCharacter::EquipTorch(ATorch* Torch)
{
	TorchComponent = NewObject<UTorchComponent>(this, UTorchComponent::StaticClass(), TEXT("TorchComponent"));

	if (TorchComponent && Torch)
	{
		AddComponentByClass(UTorchComponent::StaticClass(), false, GetActorTransform(), false);
		TorchComponent->SetTorch(Torch);
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
