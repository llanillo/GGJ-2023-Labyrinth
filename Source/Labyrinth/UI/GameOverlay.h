#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverlay.generated.h"

class UImage;
class UTextBlock;
class UWidgetAnimation;

UCLASS()
class LABYRINTH_API UGameOverlay : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* MessageTextBlock;

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* RemainingTorchTextBlock;

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* GameOverText;

public:
	UFUNCTION(BlueprintCallable)
	void ShowGameOver() const;

	UFUNCTION(BlueprintCallable)
	void SetMessage(const FText& NewText) const;

	UFUNCTION(BlueprintCallable)
	void SetRemainingTorchText(const FText& NewText) const;

	UFUNCTION(BlueprintCallable)
	void HideMessage() const;

protected:
	virtual bool Initialize() override;
};
