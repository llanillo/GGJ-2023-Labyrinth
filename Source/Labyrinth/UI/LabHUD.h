// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LabHUD.generated.h"

class UGameOverlay;

UCLASS()
class LABYRINTH_API ALabHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameOverlay> GameOverlayClass;

	UPROPERTY(BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	UGameOverlay* GameOverlay;

public:
	UFUNCTION(BlueprintCallable)
	void ShowGameOver() const;
	
	UFUNCTION(BlueprintCallable)
	void ShowMessage(const FString& Message) const;

	UFUNCTION(BlueprintCallable)
	void ShowRemainingText(const FString& Message) const;

	UFUNCTION(BlueprintCallable)
	static void ShowInitialStory();

	UFUNCTION(BlueprintCallable)
	void HideMessage() const;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	// Sets default values for this actor's properties
	ALabHUD();
};
