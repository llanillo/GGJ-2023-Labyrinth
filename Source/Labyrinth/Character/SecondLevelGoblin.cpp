#include "SecondLevelGoblin.h"

#include "AIController.h"

ASecondLevelGoblin::ASecondLevelGoblin()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASecondLevelGoblin::MoveToLocation(const FVector& Location) const
{
	AAIController* ControllerAI = GetController<AAIController>();
	ControllerAI->MoveToLocation(Location, true, true, true, true);
}
