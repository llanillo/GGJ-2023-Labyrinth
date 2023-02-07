#include "SleepingGoblin.h"

#include "AIController.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASleepingGoblin::ASleepingGoblin() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	bCanFollow = true;

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	
	GetSphereComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereBeginOverlap);
	GetSphereComponent()->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereEndOverlap);
}

void ASleepingGoblin::BeginPlay()
{
	Super::BeginPlay();
}

void ASleepingGoblin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LabCharacter && bCanFollow)
	{
		if (AAIController* GoblinController = GetController<AAIController>())
		{
			GoblinController->MoveToLocation(LabCharacter->GetActorLocation(), 10.f);
		}
	}
}

void ASleepingGoblin::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bBFromSweep,
                                           const FHitResult& SweepResult)
{
	if (ALabCharacter* PlayerCharacter = Cast<ALabCharacter>(OtherActor))
	{
		LabCharacter = PlayerCharacter;
	}
}

void ASleepingGoblin::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if (ALabCharacter* PlayerCharacter = Cast<ALabCharacter>(OtherActor))
	{
		LabCharacter = nullptr;
	}
}
