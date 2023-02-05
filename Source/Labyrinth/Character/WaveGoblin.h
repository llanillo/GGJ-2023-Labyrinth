#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WaveGoblin.generated.h"

class UBoxComponent;
class ASpawnTriggerBox;

UCLASS(ClassGroup=LAB)
class LABYRINTH_API AWaveGoblin : public ACharacter
{
	GENERATED_BODY()

public:
	AWaveGoblin();
	
	UFUNCTION()
	void MoveToLocation(const FVector& Location) const;
};
