#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LabGameInstance.generated.h"

UCLASS(BlueprintType)
class LABYRINTH_API ULabGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	FName MainMenuLevelName;

public:
	FORCEINLINE const FName& GetMainMenuLevelName() const { return MainMenuLevelName; }
};
