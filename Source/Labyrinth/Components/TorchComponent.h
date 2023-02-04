#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TorchComponent.generated.h"

UCLASS(BlueprintType)
class LABYRINTH_API UTorchComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* TorchMeshComponent;

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

protected:
	virtual void BeginPlay() override;
};


