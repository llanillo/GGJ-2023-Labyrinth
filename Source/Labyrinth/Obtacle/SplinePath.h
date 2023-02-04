#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePath.generated.h"

class UStaticMeshComponent;
class USplineComponent;

UCLASS()
class LABYRINTH_API ASplinePath : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = true))
	AActor* AActorToMoveAlongSpline;
	
	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	USplineComponent* SplineComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = true))
	float SplineMovementRate;

public:
	ASplinePath();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartMovementAlongSpline();
};
