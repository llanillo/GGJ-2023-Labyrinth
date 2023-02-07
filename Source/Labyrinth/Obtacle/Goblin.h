#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Goblin.generated.h"

class USphereComponent;

UCLASS(ClassGroup=LAB)
class LABYRINTH_API AGoblin : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	float Damage;

	UFUNCTION()
	void OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	                 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                  UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bBFromSweep,
	                                  const FHitResult& SweepResult);

public:
	AGoblin();

	FORCEINLINE USphereComponent* GetSphereComponent() const { return SphereComponent; }
};
