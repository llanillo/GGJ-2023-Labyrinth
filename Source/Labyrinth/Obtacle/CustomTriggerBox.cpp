#include "CustomTriggerBox.h"

ACustomTriggerBox::ACustomTriggerBox()
{
	PrimaryActorTick.bCanEverTick = true;

	Tag = SpawnName;
}