#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "JumpScareTriggerBox.generated.h"

UCLASS()
class LABYRINTH_API AJumpScareTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                           UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bBFromSweep,
	                           const FHitResult& SweepResult);

public:
	AJumpScareTriggerBox();
};
