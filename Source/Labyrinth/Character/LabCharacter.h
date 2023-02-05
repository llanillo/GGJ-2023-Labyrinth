// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LabCharacter.generated.h"

class AWallTorch;
class UTorchComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class USphereComponent;

UCLASS()
class LABYRINTH_API ALabCharacter : public ACharacter
{
	GENERATED_BODY()

	/*
	 * Components
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* FirstPersonMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UTorchComponent* TorchComponent;

	/*
	 * Game
	 */

	UPROPERTY(BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = true))
	AWallTorch* LastWallTorch;

	/*
	 * Dependencies
	 */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	float DashForce;

	/*
	 * Character actions
	 */
	UFUNCTION(BlueprintCallable)
	void Dash();

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);

public:
	UFUNCTION(BlueprintCallable)
	void EquipTorch(ATorch* Torch);

	UFUNCTION(BlueprintCallable)
	void IncreaseTorch(float Value) const;

	UFUNCTION(BlueprintCallable)
	void ReduceTorch(float Value) const;

	UFUNCTION(BlueprintCallable)
	void SetWallTorch(AWallTorch* WallTorch);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	ALabCharacter();

	FORCEINLINE USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMeshComponent; }

	FORCEINLINE AWallTorch* GetLastWallTorch() const { return LastWallTorch; }
};
