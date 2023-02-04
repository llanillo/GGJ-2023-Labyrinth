#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goblin.generated.h"

UCLASS()
class LABYRINTH_API AGoblin : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

public:
	AGoblin();
};
