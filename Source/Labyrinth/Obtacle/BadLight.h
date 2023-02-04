#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "BadLight.generated.h"

UCLASS()
class LABYRINTH_API ABadLight : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	USplineComponent* SplineComponent;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartMovementAlongSpline();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	// Sets default values for this actor's properties
	ABadLight();
};
