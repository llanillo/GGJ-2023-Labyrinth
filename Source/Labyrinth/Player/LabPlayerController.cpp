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
	checkf(CrouchAction, TEXT("[ALabPlayerController - BeginPlay: CrouchAction is not valid]"));
	checkf(InteractAction, TEXT("[ALabPlayerController - BeginPlay: InteractAction is not valid]"));
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

void ALabPlayerController::ShowDamageIndicator(const TSubclassOf<UCameraShakeBase>& CameraShakeBase)
{
	GameHUD = GameHUD ? GameHUD : GetHUD<ALabHUD>();
	checkf(GameHUD, TEXT("[ALabPlayerController - ShowDamageIndicator: HUD is not valid]"));

	PlayerCameraManager->StartCameraShake(CameraShakeBase);
	GameHUD->ShowDamageIndicator();
}

void ALabPlayerController::ShowJumpScare()
{
	GameHUD = GameHUD ? GameHUD : GetHUD<ALabHUD>();
	checkf(GameHUD, TEXT("[ALabPlayerController - ShowMessageHUD: HUD is not valid]"));

	GameHUD->ShowJumpScare();
}

void ALabPlayerController::ShowMessageHUD(const FString& Message)
{
	GameHUD = GameHUD ? GameHUD : GetHUD<ALabHUD>();
	checkf(GameHUD, TEXT("[ALabPlayerController - ShowMessageHUD: HUD is not valid]"));

	GameHUD->ShowMessage(Message);
}

void ALabPlayerController::ShowRemainingTorch(const FString& RemainingTorch)
{
	GameHUD = GameHUD ? GameHUD : GetHUD<ALabHUD>();
	checkf(GameHUD, TEXT("[ALabPlayerController - ShowMessageHUD: HUD is not valid]"));

	GameHUD->ShowRemainingText(RemainingTorch);
}

void ALabPlayerController::ShowGameOver()
{
	GameHUD = GameHUD ? GameHUD : GetHUD<ALabHUD>();
	checkf(GameHUD, TEXT("[ALabPlayerController - ShowMessageHUD: HUD is not valid]"));

	GameHUD->ShowGameOver();
}

void ALabPlayerController::HideMessageHUD()
{
	GameHUD = GameHUD ? GameHUD : GetHUD<ALabHUD>();
	checkf(GameHUD, TEXT("[ALabPlayerController - ShowMessageHUD: HUD is not valid]"));

	GameHUD->HideMessage();
}
