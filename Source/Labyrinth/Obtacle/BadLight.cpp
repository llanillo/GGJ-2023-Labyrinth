#include "BadLight.h"

ABadLight::ABadLight()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineLineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
}

void ABadLight::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABadLight::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

