#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TorchComponent.generated.h"

UCLASS(BlueprintType)
class LABYRINTH_API UTorchComponent : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* TorchMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	float MaxTorch;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	float RemainingTorch;

public:

	UTorchComponent();

	UFUNCTION(BlueprintCallable)
	void DecreaseTorch(float Value);

};


