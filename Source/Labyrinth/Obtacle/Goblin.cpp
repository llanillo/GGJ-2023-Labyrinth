#include "Goblin.h"

#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "Labyrinth/Character/LabCharacter.h"

AGoblin::AGoblin()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.f;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(100.f);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereBeginOverlap);
}

void AGoblin::BeginPlay()
{
	Super::BeginPlay();
}

void AGoblin::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                          FVector NormalImpulse, const FHitResult& Hit)
{
	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(OtherActor))
	{
		if (Damage > 0)
		{
			const FDamageEvent DamageEvent;
			LabCharacter->TakeDamage(Damage, DamageEvent, Controller, this);
			SphereComponent->OnComponentHit.RemoveAll(this);
			Destroy();
		}
	}
}

inline void AGoblin::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bBFromSweep,
                                          const FHitResult& SweepResult)
{
	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(OtherActor))
	{
		if (Damage > 0)
		{
			const FDamageEvent DamageEvent;
			LabCharacter->TakeDamage(Damage, DamageEvent, Controller, this);
			SphereComponent->OnComponentBeginOverlap.RemoveAll(this);
			Destroy();
		}
	}
}