#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "PickupComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickup, ACharacter*, CharacterWhoPickup);

UCLASS(ClassGroup=(LAB), meta=(BlueprintSpawnableComponent))
class LABYRINTH_API UPickupComponent : public USphereComponent
{
	GENERATED_BODY()

	/*
	 * Callbacks
	 */
	UFUNCTION()
	void OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	              UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bBFromSweep,
	              const FHitResult& SweepResult);

public:
	// Sets default values for this component's properties
	UPickupComponent();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnPickup OnPickupEvent;
};
