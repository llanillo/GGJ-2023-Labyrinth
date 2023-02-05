#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EndWaveTriggerBox.generated.h"

/*
 * Objective box where goblins are going to
 */
UCLASS()
class LABYRINTH_API AEndWaveTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

	UFUNCTION()
	void OnTriggerBoxOverlap(UPrimitiveComponent*
	                         OverlappedComponent, AActor* OtherActor, UPrimitiveComponent*
	                         OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                         const FHitResult& SweepResult);

public:
	// Sets default values for this actor's properties
	AEndWaveTriggerBox();
};
