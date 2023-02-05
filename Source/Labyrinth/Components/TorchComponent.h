﻿#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TorchComponent.generated.h"

class ATorch;

UCLASS(BlueprintType)
class LABYRINTH_API UTorchComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	ATorch* Torch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	int32 MaximumFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	int32 RemainingFire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = truw))
	int32 DecreaseAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = truw))
	bool bCanIncreaseTorch;

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	int32 IncreaseTorchCooldown;
	
	UPROPERTY()
	FTimerHandle DecreaseTorchHandle;

	UPROPERTY()
	FTimerHandle IncreaseTorchHandle;

	UFUNCTION()
	void OnIncreaseTorchTimeout();

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
