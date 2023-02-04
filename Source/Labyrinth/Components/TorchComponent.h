#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TorchComponent.generated.h"

class ATorch;

UCLASS(BlueprintType)
class LABYRINTH_API UTorchComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	ATorch* Torch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	float MaximumFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	float RemainingFire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = truw))
	float DecreaseAmount;

	UPROPERTY()
	FTimerHandle DecreaseTorchHandle;

public:
	UTorchComponent();

	UFUNCTION(BlueprintCallable)
	void IncreaseTorch(float Value);

	UFUNCTION(BlueprintCallable)
	void DecreaseTorch(float Value);

	FORCEINLINE void SetTorch(ATorch* NewTorch) { Torch = NewTorch; }

protected:
	virtual void BeginPlay() override;
};
