#include "LabPlayerController.h"

#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Labyrinth/UI/LabHUD.h"

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

void ALabPlayerController::ShowMessageHUD(const FString& Message) const
{
	const ALabHUD* LabHUD = GetHUD<ALabHUD>();
	checkf(LabHUD, TEXT("[ALabPlayerController - ShowMessageHUD: HUD is not valid]"));

	LabHUD->ShowMessage(Message);
}

void ALabPlayerController::ShowRemainingTorch(const FString& RemainingTorch) const
{
	const ALabHUD* LabHUD = GetHUD<ALabHUD>();
	checkf(LabHUD, TEXT("[ALabPlayerController - ShowRemainingTorch: HUD is not valid]"));

	LabHUD->ShowRemainingText(RemainingTorch);
}

void ALabPlayerController::HideMessageHUD() const
{
	const ALabHUD* LabHUD = GetHUD<ALabHUD>();
	checkf(LabHUD, TEXT("[ALabPlayerController - HideMessageHUD: HUD is not valid]"));

	LabHUD->HideMessage();
}
