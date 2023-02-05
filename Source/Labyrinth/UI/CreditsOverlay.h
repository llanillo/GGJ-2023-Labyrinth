#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsOverlay.generated.h"

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackButtonClicked);

UCLASS(ClassGroup=LAB)
class LABYRINTH_API UCreditsOverlay : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* BackButton;

	UFUNCTION(BlueprintCallable)
	void OnBackButtonClicked();

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnBackButtonClicked OnBackClicked;
	
	virtual bool Initialize() override;
};
