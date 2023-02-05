#include "PickupComponent.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

UPickupComponent::UPickupComponent()
{
	SphereRadius = 100.f;

	OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentOverlap);
	OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentFinishOverlap);
}

void UPickupComponent::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp,
                                          int OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		OnCharacterBeginOverlap.Broadcast(Character);
	}
}

void UPickupComponent::OnComponentFinishOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		OnCharacterEndOverlap.Broadcast(Character);
	}
}
