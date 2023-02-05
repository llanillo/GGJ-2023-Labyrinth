#include "WaveGoblin.h"

#include "AIController.h"

AWaveGoblin::AWaveGoblin()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AWaveGoblin::MoveToLocation(const FVector& Location) const
{
	AAIController* ControllerAI = GetController<AAIController>();
	ControllerAI->MoveToLocation(Location, true, true, true, true);
}
