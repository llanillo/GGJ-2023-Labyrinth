#include "JumpScareTriggerBox.h"

#include "Components/ShapeComponent.h"
#include "Labyrinth/Character/LabCharacter.h"
#include "Labyrinth/Player/LabPlayerController.h"

AJumpScareTriggerBox::AJumpScareTriggerBox()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCollisionComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBeginOverlap);
}

void AJumpScareTriggerBox::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	if(const ALabCharacter* LabCharacter = Cast<ALabCharacter>(OtherActor))
	{
		if(ALabPlayerController* LabPlayerController = Cast<ALabPlayerController>(LabCharacter->Controller))
		{
			LabPlayerController->ShowJumpScare();
			GetCollisionComponent()->OnComponentBeginOverlap.RemoveAll(this);
		}
	}
}
