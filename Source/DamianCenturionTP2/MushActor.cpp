// Fill out your copyright notice in the Description page of Project Settings.

#include "MushActor.h"


// Sets default values
AMushActor::AMushActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMushActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMushActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


