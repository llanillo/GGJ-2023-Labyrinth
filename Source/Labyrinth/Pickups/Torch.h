#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Torch.generated.h"

class USkeletalMeshComponent;
class UPickupComponent;

UCLASS(ClassGroup=LAB)
class LABYRINTH_API ATorch : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* TorchNMeshComponent;

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	UPickupComponent* PickupComponent;

	/*
	 * Callbacks
	 */
	UFUNCTION()
	void OnPickup(ACharacter* CharacterWhoPickup);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	// Sets default values for this actor's properties
	ATorch();
};
