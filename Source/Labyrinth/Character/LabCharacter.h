// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LabCharacter.generated.h"

class UTorchComponent;
class USkeletalMeshComponent;
class UCameraComponent;

UCLASS()
class LABYRINTH_API ALabCharacter : public ACharacter
{
	GENERATED_BODY()

	/* Hands mesh comopnent */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* FirstPersonMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UTorchComponent* TorchComponent;

	/* Used to pick up items */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	USphereComponent* SphereComponent;

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

	/*
	 * Callbacks
	 */

	UFUNCTION(BlueprintCallable)
	void OnActorBeginoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bBFromSweep,
	                         const FHitResult& SweepResult);

public:
	UFUNCTION(BlueprintCallable)
	void EquipTorch();

	UFUNCTION(BlueprintCallable)
	void ReduceTorch(float Value);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	ALabCharacter();
};

