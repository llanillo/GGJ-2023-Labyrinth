#include "LabCharacter.h"

#include "EnhancedInputComponent.h"
#include "Labyrinth/Player/LabPlayerController.h"


ALabCharacter::ALabCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DashForce = 50.f;
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
	}
}

void ALabCharacter::Dash()
{
	if(Controller)
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
