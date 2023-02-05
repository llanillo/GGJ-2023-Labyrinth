#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EndWaveTriggerBox.generated.h"

UCLASS()
class LABYRINTH_API AEndWaveTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

	UFUNCTION()
	void OnActorOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	// Sets default values for this actor's properties
	AEndWaveTriggerBox();
};
