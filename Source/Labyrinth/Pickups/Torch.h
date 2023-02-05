#pragma once

#include "CoreMinimal.h"
#include "Obtainable.h"
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
class LABYRINTH_API ATorch : public AObtainable
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	EFireLevel CurrentFireLevel;
	
public:
	UFUNCTION( BlueprintCallable)
	void SetFireLevel(EFireLevel FireLevel);
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnCharacterBeginOverlap(ACharacter* CharacterWhoPickup) override;
public:
	// Sets default values for this actor's properties
	ATorch();
};
