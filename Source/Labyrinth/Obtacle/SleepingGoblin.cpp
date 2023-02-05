#include "SleepingGoblin.h"

#include "AIController.h"
#include "Components/SphereComponent.h"

ASleepingGoblin::ASleepingGoblin()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(100.f);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereBeginOverlap);
}

void ASleepingGoblin::BeginPlay()
{
	Super::BeginPlay();
}

void ASleepingGoblin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASleepingGoblin::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bBFromSweep,
                                           const FHitResult& SweepResult)
{
	if (ALabCharacter* PlayerCharacter = Cast<ALabCharacter>(OtherActor))
	{
		LabCharacter = PlayerCharacter;

		if (AAIController* GoblinController = GetController<AAIController>())
		{
			GoblinController->MoveToLocation(PlayerCharacter->GetActorLocation(), 10.f);
		}
	}
}
