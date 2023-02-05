// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CustomTriggerBox.generated.h"

UCLASS()
class LABYRINTH_API ACustomTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	FName Tag;

public:
	// Sets default values for this actor's properties
	ACustomTriggerBox();

	inline static const FName SpawnName = "GoblinSpawner";

	FORCEINLINE const FName& GetTag() const { return Tag; }
};
