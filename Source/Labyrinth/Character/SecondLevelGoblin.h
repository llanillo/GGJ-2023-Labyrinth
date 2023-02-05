#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SecondLevelGoblin.generated.h"

class UBoxComponent;
class ACustomTriggerBox;

UCLASS(ClassGroup=LAB)
class LABYRINTH_API ASecondLevelGoblin : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	ACustomTriggerBox* DestinationTrigger;
	
public:
	ASecondLevelGoblin();
	
	UFUNCTION()
	void MoveToLocation(const FVector& Location) const;
};
