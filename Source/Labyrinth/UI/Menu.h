#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

class UButton;

UCLASS()
class LABYRINTH_API UMenu : public UUserWidget
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
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;
};
