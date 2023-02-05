#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LabGameMode.generated.h"

class ASpawnTriggerBox;
class AWaveGoblin;
class AEndWaveTriggerBox;

UCLASS(BlueprintType)
class LABYRINTH_API ALabGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	TSubclassOf<AWaveGoblin> WaveGoblinClass;

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	ASpawnTriggerBox* GoblinSpawner;

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	AEndWaveTriggerBox* EndWaveTriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	float MinTimeToSpawnSecondLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	float MaxTimeToSpawnSecondLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	float GameOverDelay;

	UPROPERTY()
	FTimerHandle SecondLevelHandle;

	UPROPERTY()
	FTimerHandle GameOverHandle;

	/*
	 * Callbacks
	 */
	UFUNCTION()
	void OnGoblinSpawn();

	UFUNCTION()
	void OnGameOverTimeout() ;

public:
	UFUNCTION(BlueprintCallable)
	void StartGoblinWave();

	UFUNCTION(BlueprintCallable)
	void FinishGoblinWave();

	UFUNCTION(BlueprintCallable)
	void GameOver() ;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	ALabGameMode();

	FORCEINLINE ASpawnTriggerBox* GetSecondLevelSpawnTrigger() const { return GoblinSpawner; }
};
