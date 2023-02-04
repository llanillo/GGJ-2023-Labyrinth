// Fill out your copyright notice in the Description page of Project Settings.


#include "LabHUD.h"


// Sets default values
ALabHUD::ALabHUD()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ALabHUD::ShowInitialStory()
{
}

// Called when the game starts or when spawned
void ALabHUD::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALabHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

