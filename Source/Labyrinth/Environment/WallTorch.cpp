#include "WallTorch.h"
#include "NiagaraComponent.h"
#include "Labyrinth/Character/LabCharacter.h"
#include "Labyrinth/Components/PickupComponent.h"

AWallTorch::AWallTorch()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;
	
	FireNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	FireNiagaraComponent->SetupAttachment(RootComponent);
	FireNiagaraComponent->SetAutoActivate(false);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("SphereComponent"));
	PickupComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PickupComponent->OnCharacterBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnWallTorchBeginOverlap);
	PickupComponent->OnCharacterEndOverlap.AddUniqueDynamic(this, &ThisClass::OnWallTorchEndOverlap);
	PickupComponent->SetupAttachment(RootComponent);
}

void AWallTorch::BeginPlay()
{
	Super::BeginPlay();
}

void AWallTorch::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWallTorch::LightUp()
{
	CurrentLightStatus = ELightStatus::Els_On;
	FireNiagaraComponent->Activate();
	UE_LOG(LogTemp, Warning, TEXT("[AWallTorch - LightUp: Torch light up]"));
}

void AWallTorch::OnWallTorchBeginOverlap(ACharacter* CharacterWhoPickup)
{
	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(CharacterWhoPickup))
	{
		LabCharacter->SetWallTorch(this);
	}
}

void AWallTorch::OnWallTorchEndOverlap(ACharacter* CharacterWhoPickup)
{
	if (ALabCharacter* LabCharacter = Cast<ALabCharacter>(CharacterWhoPickup))
	{
		LabCharacter->SetWallTorch(nullptr);
	}
}
