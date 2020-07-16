// Fill out your copyright notice in the Description page of Project Settings.

#include "RotativeFireObstacle.h"


// Sets default values
ARotativeFireObstacle::ARotativeFireObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARotativeFireObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotativeFireObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto rot = GetActorRotation();

	FRotator NewRotation = FRotator(rot.Pitch + rotationSpeed * DeltaTime, rot.Yaw, rot.Roll);

	SetActorRotation(NewRotation, ETeleportType::None);
}

