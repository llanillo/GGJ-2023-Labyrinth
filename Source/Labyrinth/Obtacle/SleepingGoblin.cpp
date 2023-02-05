#include "SleepingGoblin.h"

#include "AIController.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASleepingGoblin::ASleepingGoblin()
{
	PrimaryActorTick.bCanEverTick = true;

	bCanFollow = true;

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(300.f);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereEndOverlap);
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