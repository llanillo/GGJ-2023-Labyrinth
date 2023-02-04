#include "SplinePath.h"

#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"

ASplinePath::ASplinePath()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineLineComponent"));
	SplineComponent->SetupAttachment(RootComponent);

	SplineMovementRate = 5.f;
}