// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabHUD.generated.h"

UCLASS()
class LABYRINTH_API ALabHUD : public AActor
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void ShowInitialStory();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	// Sets default values for this actor's properties
	ALabHUD();
};
