// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabHUD.generated.h"

class UGameOverlay;

UCLASS()
class LABYRINTH_API ALabHUD : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameOverlay> GameOverlayClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	UGameOverlay* GameOverlay;

public:
	UFUNCTION(BlueprintCallable)
	void SetGameMessage(const FString& Message) const;

	UFUNCTION(BlueprintCallable)
	static void ShowInitialStory();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	// Sets default values for this actor's properties
	ALabHUD();
};
