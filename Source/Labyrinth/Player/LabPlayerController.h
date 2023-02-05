#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LabPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class LABYRINTH_API ALabPlayerController : public APlayerController
{
	GENERATED_BODY()

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
	void ShowMessageHUD(const FString& Message) const;

	UFUNCTION(BlueprintCallable)
	void ShowRemainingTorch(const FString& RemainingTorch) const;

	UFUNCTION(BlueprintCallable)
	void ShowGameOver() const;
	
	UFUNCTION(BlueprintCallable)
	void HideMessageHUD() const;

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
