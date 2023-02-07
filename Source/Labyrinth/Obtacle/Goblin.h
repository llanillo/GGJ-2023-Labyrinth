#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Goblin.generated.h"

UCLASS(ClassGroup=LAB)
class LABYRINTH_API AGoblin : public ACharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	AGoblin();
};
