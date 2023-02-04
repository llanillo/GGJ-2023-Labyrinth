#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverlay.generated.h"

class UImage;
class UWidgetAnimation;

UCLASS()
class LABYRINTH_API UGameOverlay : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = true))
	UImage* DamageIndicatorImage;

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* DamageIndicatorAnim;

public:

	UFUNCTION(BlueprintCallable)
	void StartDamageIndicatorAnimation();

	UFUNCTION(BlueprintCallable)
	void OnFinishedDamageIndicatorAnimation();
};
