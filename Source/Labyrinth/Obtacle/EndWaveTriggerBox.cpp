#include "EndWaveTriggerBox.h"

#include "Goblin.h"


AEndWaveTriggerBox::AEndWaveTriggerBox()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEndWaveTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnActorOverlap);
}

void AEndWaveTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEndWaveTriggerBox::OnActorOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(AGoblin* Goblin = Cast<AGoblin>(OtherActor))
	{
		Goblin->Destroy();
	}
}

