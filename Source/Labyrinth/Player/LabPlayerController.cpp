#include "LabPlayerController.h"

#include "EnhancedInputSubsystems.h"

ALabPlayerController::ALabPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALabPlayerController::BeginPlay()
{
	Super::BeginPlay();

	checkf(LookAction, TEXT("[ALabPlayerController - BeginPlay: LookAction is not valid]"));
	checkf(JumpAction, TEXT("[ALabPlayerController - BeginPlay: JumpAction is not valid]"));
	checkf(MoveAction, TEXT("[ALabPlayerController - BeginPlay: MoveAction is not valid]"));
	checkf(DashAction, TEXT("[ALabPlayerController - BeginPlay: DashAction is not valid]"));
}

void ALabPlayerController::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	checkf(InputMappingContext, TEXT("[ALabPlayerController - SetupInputComponent: InputMappingContext is not valid]"));

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}