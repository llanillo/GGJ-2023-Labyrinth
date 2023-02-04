#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireTorchPickup.generated.h"

class UPickupComponent;
class ACharacter;

UCLASS(ClassGroup=LAB)
class LABYRINTH_API AFireTorchPickup : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	UPickupComponent* PickupComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	float RechargeValue;

	/*
	 * Callbacks
	 */
	UFUNCTION()
	void OnPickUp(ACharacter* CharacterWhoPickup);

public:
	AFireTorchPickup();

	FORCEINLINE float GetRechargeValue() const { return RechargeValue; }
};
