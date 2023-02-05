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
	int32 MaximumFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	int32 RemainingFire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = truw))
	int32 DecreaseAmount;

	UPROPERTY()
	FTimerHandle DecreaseTorchHandle;

public:
	UTorchComponent();

	UFUNCTION(BlueprintCallable)
	void IncreaseTorch(int32 Value);

	UFUNCTION(BlueprintCallable)
	void DecreaseTorch(int32 Value);

	UFUNCTION(BlueprintCallable)
	void EquipTorch(ATorch* NewTorch);

protected:
	virtual void BeginPlay() override;
};
