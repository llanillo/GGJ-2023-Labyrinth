#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsOverlay.generated.h"

class UButton;

UCLASS(ClassGroup=LAB)
class LABYRINTH_API UCreditsOverlay : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = true))
	UButton* BackButton;

	UFUNCTION(BlueprintCallable)
	void OnBackButtonClicked();
	
public:
	virtual bool Initialize() override;
	// TODO
};
