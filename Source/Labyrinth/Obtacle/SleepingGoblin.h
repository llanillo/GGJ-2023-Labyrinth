﻿#pragma once

#include "CoreMinimal.h"
#include "Goblin.h"
#include "Labyrinth/Character/LabCharacter.h"
#include "SleepingGoblin.generated.h"

class USphereComponent;

UCLASS()
class LABYRINTH_API ASleepingGoblin : public AGoblin
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	USphereComponent* SphereComponent;

	UPROPERTY(BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	ALabCharacter* LabCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	bool bCanFollow;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                          AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                          int OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp, int OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	// Sets default values for this character's properties
	ASleepingGoblin();
};
