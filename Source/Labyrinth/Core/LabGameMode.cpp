#include "LabGameMode.h"

#include "EngineUtils.h"
#include "LabGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Labyrinth/Character/WaveGoblin.h"
#include "Labyrinth/Obtacle/CustomTriggerBox.h"
#include "Labyrinth/Obtacle/EndWaveTriggerBox.h"

ALabGameMode::ALabGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

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

		if (ACustomTriggerBox* TriggerBox = Cast<ACustomTriggerBox>(*It))
		{
			GoblinSpawner = TriggerBox;
		}
	}

	StartSecondLevelSpawn();
}

void ALabGameMode::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabGameMode::StartSecondLevelSpawn()
{
	if (EndWaveTriggerBox && GoblinSpawner)
	{
		const float RandomTime = FMath::RandRange(MinTimeToSpawnSecondLevel, MaxTimeToSpawnSecondLevel);
		GetWorldTimerManager().SetTimer(SecondLevelHandle, this, &ThisClass::OnGoblinSpawn, RandomTime);
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

void ALabGameMode::GameOver() const
{
	if (const ULabGameInstance* LabGameInstance = GetGameInstance<ULabGameInstance>())
	{
		UGameplayStatics::OpenLevel(this, LabGameInstance->GetMainMenuLevelName(), true);
	}
}
