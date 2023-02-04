#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Torch.generated.h"

class UStaticMeshComponent;
class UPickupComponent;
class UNiagaraComponent;

UENUM()
enum class EFireLevel
{
	Efl_Low UMETA(DisplayName = "Low"),
	Efl_Half UMETA(DisplayName = "Half"),
	Efl_High UMETA(DisplayName = "High"),
	Efl_Max UMETA(DisplayName = "Max")
};

UCLASS(ClassGroup=LAB)
class LABYRINTH_API ATorch : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	USceneComponent* RootSceneComponent;
	
	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* TorchNMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	UNiagaraComponent* FireParticlesSystem;
	
	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	UPickupComponent* PickupComponent;

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	EFireLevel CurrentFireLevel;
	
	/*
	 * Callbacks
	 */
	UFUNCTION()
	void OnPickup(ACharacter* CharacterWhoPickup);

public:
	UFUNCTION( BlueprintCallable)
	void SetFireLevel(EFireLevel FireLevel);
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	// Sets default values for this actor's properties
	ATorch();
};
