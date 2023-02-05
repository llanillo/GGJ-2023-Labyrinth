#include "EndWaveTriggerBox.h"

#include "Goblin.h"
#include "Components/ShapeComponent.h"


AEndWaveTriggerBox::AEndWaveTriggerBox()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCollisionComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBoxOverlap);
}

void AEndWaveTriggerBox::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                             const FHitResult& SweepResult)
{
	if (AGoblin* Goblin = Cast<AGoblin>(OtherActor))
	{
		Goblin->Destroy();
	}
}