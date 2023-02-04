#include "LabCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Labyrinth/Components/TorchComponent.h"
#include "Labyrinth/Pickups/FireTorchPickup.h"
#include "Labyrinth/Player/LabPlayerController.h"


ALabCharacter::ALabCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DashForce = 50.f;

	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMeshComponent"));
	FirstPersonMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // TODO: Cambiar¿?¿
	FirstPersonMeshComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(200.f);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnActorBeginoverlap);
	// TorchComponent = CreateDefaultSubobject<UTorchComponent>(TEXT("TorchComponent"));
}

void ALabCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALabCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const ALabPlayerController* LabPlayerController = Cast<ALabPlayerController>(Controller);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (LabPlayerController && EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(LabPlayerController->GetMoveAction(), ETriggerEvent::Triggered, this,
		                                   &ThisClass::Move);
		EnhancedInputComponent->BindAction(LabPlayerController->GetLookAction(), ETriggerEvent::Triggered, this,
		                                   &ThisClass::Look);
		EnhancedInputComponent->BindAction(LabPlayerController->GetJumpAction(), ETriggerEvent::Triggered, this,
		                                   &ThisClass::Jump);
		EnhancedInputComponent->BindAction(LabPlayerController->GetDashAction(), ETriggerEvent::Triggered, this,
		                                   &ThisClass::Dash);
	}
}

void ALabCharacter::OnActorBeginoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bBFromSweep,
                                               const FHitResult& SweepResult)
{
	if(AFireTorchPickup* FireTorchPickup = Cast<AFireTorchPickup>(OtherActor))
	{
		// TODOO
	}
}

void ALabCharacter::Dash()
{
	if (Controller)
	{
		LaunchCharacter(GetActorForwardVector() * DashForce, true, false);
	}
}

void ALabCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ALabCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void ALabCharacter::EquipTorch()
{
	TorchComponent = NewObject<UTorchComponent>(this, UTorchComponent::StaticClass(), TEXT("TorchComponent"));

	if (TorchComponent)
	{
		AddComponentByClass(UTorchComponent::StaticClass(), false, GetActorTransform(), false);
	}
}

void ALabCharacter::ReduceTorch(const float Value)
{
	if (TorchComponent)
	{
		TorchComponent->DecreaseTorch(Value);
	}
}
