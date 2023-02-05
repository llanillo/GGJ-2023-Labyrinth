#include "LabGameMode.h"

#include "EngineUtils.h"
#include "LabGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Labyrinth/Character/WaveGoblin.h"
#include "Labyrinth/Obtacle/SpawnTriggerBox.h"
#include "Labyrinth/Obtacle/EndWaveTriggerBox.h"
#include "Labyrinth/Player/LabPlayerController.h"

ALabGameMode::ALabGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	GameOverDelay = 3.f;
	MinTimeToSpawnSecondLevel = 1.f;
	MaxTimeToSpawnSecondLevel = 3.f;
}

void ALabGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(WaveGoblinClass, TEXT("[ALabGameMode - BeginPlay: WaveGoblinClass is not valid]"));

	for (TActorIterator<ATriggerBox> It(GetWorld()); It; ++It)
	{
		if (AEndWaveTriggerBox* TriggerBox = Cast<AEndWaveTriggerBox>(*It))
		{
			EndWaveTriggerBox = TriggerBox;
		}

		if (ASpawnTriggerBox* TriggerBox = Cast<ASpawnTriggerBox>(*It))
		{
			GoblinSpawner = TriggerBox;
		}
	}
}

void ALabGameMode::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabGameMode::StartGoblinWave()
{
	if (EndWaveTriggerBox && GoblinSpawner)
	{
		const float RandomTime = FMath::RandRange(MinTimeToSpawnSecondLevel, MaxTimeToSpawnSecondLevel);
		GetWorldTimerManager().SetTimer(SecondLevelHandle, this, &ThisClass::OnGoblinSpawn, RandomTime);
	}
}

void ALabGameMode::FinishGoblinWave()
{
	if (SecondLevelHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(SecondLevelHandle);
	}
}

void ALabGameMode::OnGoblinSpawn()
{
	if (EndWaveTriggerBox && GoblinSpawner)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = GetOwner();
		ActorSpawnParameters.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		ActorSpawnParameters.Instigator = GetInstigator();

		FVector SpawnPositionOrigin;
		FVector SpawnPositionExtent;

		GoblinSpawner->GetActorBounds(false, SpawnPositionOrigin, SpawnPositionExtent, false);
		const FVector RandomSpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(
			SpawnPositionOrigin, SpawnPositionExtent);

		if (AWaveGoblin* SecondLevelGoblin = GetWorld()->SpawnActor<AWaveGoblin>(
			WaveGoblinClass, RandomSpawnLocation, GoblinSpawner->GetActorRotation(),
			ActorSpawnParameters))
		{
			SecondLevelGoblin->SpawnDefaultController();

			FVector FinalPositionOrigin;
			FVector FinalPositionExtent;

			EndWaveTriggerBox->GetActorBounds(false, FinalPositionOrigin, FinalPositionExtent, false);
			const FVector DestinationLocation = UKismetMathLibrary::RandomPointInBoundingBox(
				FinalPositionOrigin, FinalPositionExtent);

			SecondLevelGoblin->MoveToLocation(DestinationLocation);
		}

		const float RandomTime = FMath::RandRange(MinTimeToSpawnSecondLevel, MaxTimeToSpawnSecondLevel);
		GetWorldTimerManager().SetTimer(SecondLevelHandle, this, &ThisClass::OnGoblinSpawn, RandomTime);
	}
}

void ALabGameMode::GameOver()
{
	ALabPlayerController* LocalController = Cast<ALabPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0));
	check(LocalController);

	LocalController->ShowGameOver();
	GetWorldTimerManager().SetTimer(GameOverHandle, this, &ThisClass::OnGameOverTimeout, GameOverDelay);
}

void ALabGameMode::OnGameOverTimeout()
{
	if (GameOverHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(GameOverHandle);
	}

	if (const ULabGameInstance* LabGameInstance = GetGameInstance<ULabGameInstance>())
	{
		UGameplayStatics::OpenLevel(this, LabGameInstance->GetMainMenuLevelName(), true);
	}
}