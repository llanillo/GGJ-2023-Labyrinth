#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/DelegateCombinations.h"
#include "Delegates/DelegateCombinations.h"
#include "MenuOverlay.generated.h"

class UButton;
class UCreditsOverlay;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCreditsButtonClicked);

UCLASS()
class LABYRINTH_API UMenuOverlay : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* StartButton;

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* CreditsButton;

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* QuitButton;

	UFUNCTION(BlueprintCallable)
	void OnStartButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnCreditsButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnQuitButtonClicked();

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnCreditsButtonClicked OnCreditsClicked;
	
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;
};
