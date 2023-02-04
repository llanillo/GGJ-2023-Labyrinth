#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireTorchPickup.generated.h"

class USphereComponent;

UCLASS()
class LABYRINTH_API AFireTorchPickup : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	USphereComponent* SphereComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	float RechargeValue;

public:
	AFireTorchPickup();

	FORCEINLINE float GetRechargeValue() const { return RechargeValue; }
};
