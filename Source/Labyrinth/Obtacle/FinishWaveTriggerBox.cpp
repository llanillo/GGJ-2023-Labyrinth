#include "FinishWaveTriggerBox.h"

#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Labyrinth/Character/LabCharacter.h"
#include "Labyrinth/Core/LabGameMode.h"

AFinishWaveTriggerBox::AFinishWaveTriggerBox()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCollisionComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBoxBeginOverlap);
}

void AFinishWaveTriggerBox::OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int OtherBodyIndex,
                                                     bool bBFromSweep, const FHitResult& SweepResult)
{
	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(OtherActor))
	{
		ALabGameMode* LabGameMode = Cast<ALabGameMode>(UGameplayStatics::GetGameMode(this));
		check(LabGameMode);

		LabGameMode->FinishGoblinWave();
		GetCollisionComponent()->OnComponentBeginOverlap.RemoveAll(this);
	}
}
