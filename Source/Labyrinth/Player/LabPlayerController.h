#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LabPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ALabHUD;

UCLASS()
class LABYRINTH_API ALabPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	ALabHUD* GameHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	UInputAction* DashAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	UInputAction* CrouchAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	UInputAction* InteractAction;

public:
	UFUNCTION(BlueprintCallable)
	void ShowJumpScare();

	UFUNCTION(BlueprintCallable)
	void ShowMessageHUD(const FString& Message);

	UFUNCTION(BlueprintCallable)
	void ShowRemainingTorch(const FString& RemainingTorch);

	UFUNCTION(BlueprintCallable)
	void ShowGameOver();

	UFUNCTION(BlueprintCallable)
	void HideMessageHUD();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

public:
	ALabPlayerController();

	FORCEINLINE UInputAction* GetMoveAction() const { return MoveAction; }

	FORCEINLINE UInputAction* GetJumpAction() const { return JumpAction; }

	FORCEINLINE UInputAction* GetLookAction() const { return LookAction; }

	FORCEINLINE UInputAction* GetDashAction() const { return DashAction; }

	FORCEINLINE UInputAction* GetCrouchAction() const { return CrouchAction; }

	FORCEINLINE UInputAction* GetInteractAction() const { return InteractAction; }
};
