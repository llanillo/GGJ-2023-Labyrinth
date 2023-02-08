#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventOverlay.generated.h"

class UImage;
class UBorder;
class UWidgetAnimation;

UCLASS()
class LABYRINTH_API UEventOverlay : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = true))
	UImage* DamageIndicatorImage;

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = true))
	UBorder* JumpScareBorder;

	UPROPERTY(BlueprintReadOnly, Category = UI, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* JumpScareAnim;

	UPROPERTY(BlueprintReadOnly, Category = UI, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* DamageIndicatorAnim;
	
	UFUNCTION()
	void OnJumpScareAnimFinished();

public:
	UFUNCTION(BlueprintCallable)
	void StartDamageIndicatorAnimation();

	UFUNCTION(BlueprintCallable)
	void StartJumpScareAnimation();

protected:
	virtual bool Initialize() override;
};
