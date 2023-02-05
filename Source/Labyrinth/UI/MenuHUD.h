#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

class UMenuOverlay;
class UCreditsOverlay;

UCLASS()
class LABYRINTH_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = true))
	TSubclassOf<UMenuOverlay> MenuOverlayClass;

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = true))
	UMenuOverlay* MenuOverlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = true))
	TSubclassOf<UCreditsOverlay> CreditsOverlayClass;

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = true))
	UCreditsOverlay* CreditsOverlay;

public:
	UFUNCTION(BlueprintCallable)
	void ShowMainMenuOverlay() ;

	UFUNCTION(BlueprintCallable)
	void ShowCreditsOverlay() ;
protected:
	virtual void BeginPlay() override;

public:
	AMenuHUD();
};
