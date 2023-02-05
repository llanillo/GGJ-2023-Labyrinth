#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obtainable.generated.h"

class UPickupComponent;
class UStaticMeshComponent;
class UNiagaraComponent;
class USceneComponent;

UCLASS(ClassGroup=LAB)
class LABYRINTH_API AObtainable : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* TorchNMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	UNiagaraComponent* FireParticlesSystem;

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	UPickupComponent* PickupComponent;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/*
	 * Callbacks
	 */
	UFUNCTION()
	virtual void OnPickup(ACharacter* CharacterWhoPickup);

public:
	// Sets default values for this actor's properties
	AObtainable();

	FORCEINLINE UNiagaraComponent* GetFireParticleSystem() const { return FireParticlesSystem; }
};
