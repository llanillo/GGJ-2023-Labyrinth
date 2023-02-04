#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LabGameMode.generated.h"

UCLASS(BlueprintType)
class LABYRINTH_API ALabGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void GameOver();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	ALabGameMode();
};
