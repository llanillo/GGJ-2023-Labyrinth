#pragma once

#include "CoreMinimal.h"
#include "Obtainable.h"
#include "FireTorchPickup.generated.h"

class ACharacter;

/*
 * Reloads player's torch bar
 */
UCLASS(ClassGroup=LAB)
class LABYRINTH_API AFireTorchPickup : public AObtainable
{
	GENERATED_BODY()

	UPROPERTY (EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	float RechargeValue;

protected:

	/*
	 * Callbacks
	 */
	virtual void OnCharacterBeginOverlap(ACharacter* CharacterWhoPickup) override;

	virtual void OnCharacterEndOverlap(ACharacter* CharacterWhoPickup) override;
	
public:
	AFireTorchPickup();

	FORCEINLINE float GetRechargeValue() const { return RechargeValue; }
};
