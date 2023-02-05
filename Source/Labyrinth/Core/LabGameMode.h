#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LabGameMode.generated.h"

class ACustomTriggerBox;
class AWaveGoblin;
class AEndWaveTriggerBox;

UCLASS(BlueprintType)
class LABYRINTH_API ALabGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	TSubclassOf<AWaveGoblin> WaveGoblinClass;
	
	UPROPERTY (BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	ACustomTriggerBox* GoblinSpawner;

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	AEndWaveTriggerBox* EndWaveTriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	float MinTimeToSpawnSecondLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	float MaxTimeToSpawnSecondLevel;

	UPROPERTY()
	FTimerHandle SecondLevelHandle;

	/*
	 * Callbacks
	 */
	void OnGoblinSpawn();

public:
	UFUNCTION(BlueprintCallable)
	void StartSecondLevelSpawn();

	UFUNCTION(BlueprintCallable)
	void GameOver() const;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	ALabGameMode();

	FORCEINLINE ACustomTriggerBox* GetSecondLevelSpawnTrigger() const { return GoblinSpawner; }
};
