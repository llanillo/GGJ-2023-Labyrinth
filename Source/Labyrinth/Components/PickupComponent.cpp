#include "PickupComponent.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

UPickupComponent::UPickupComponent()
{
	SphereRadius = 100.f;
	UPrimitiveComponent::SetCollisionResponseToAllChannels(ECR_Ignore);
	UPrimitiveComponent::SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnPickup);
}

void UPickupComponent::OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                int OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	if(ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		OnPickupEvent.Broadcast(Character);
		OnPickupEvent.RemoveAll(this);
		SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
