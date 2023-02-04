#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallTorch.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class UPickupComponent;

UENUM()
enum class ELightStatus
{
	Els_On UMETA(DisplayName = "On"),
	Els_Off UMETA(DisplayName = "Off"),
	Els_Max UMETA(DisplayName = "Max")
};

UCLASS(ClassGroup=LAB)
class LABYRINTH_API AWallTorch : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UNiagaraComponent* FireNiagaraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UPickupComponent* PickupComponent;

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	ELightStatus CurrentLightStatus;

	UFUNCTION()
	void OnWallTorchBeginOverlap(ACharacter* CharacterWhoPickup);

	UFUNCTION()
	void OnWallTorchEndOverlap(ACharacter* CharacterWhoPickup);

public:
	UFUNCTION(BlueprintCallable)
	void LightUp();

	UFUNCTION(BlueprintCallable)
	void RechargeTorch();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	AWallTorch();

	FORCEINLINE ELightStatus GetWallTorchStatus() const { return CurrentLightStatus; }
};
