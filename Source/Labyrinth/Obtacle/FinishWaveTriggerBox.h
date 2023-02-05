#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "FinishWaveTriggerBox.generated.h"

/*
 * Stop the goblin spawn
 */
UCLASS()
class LABYRINTH_API AFinishWaveTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                              UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bBFromSweep,
	                              const FHitResult& SweepResult);
	// Sets default values for this actor's properties
	AFinishWaveTriggerBox();
};
