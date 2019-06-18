// Fill out your copyright notice in the Description page of Project Settings.

#include "EndLevelTriggerActor.h"


// Sets default values
AEndLevelTriggerActor::AEndLevelTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEndLevelTriggerActor::BeginPlay()
{
	Super::BeginPlay();

	_boxCollider = FindComponentByClass<UBoxComponent>();

	if (_boxCollider)
		_boxCollider->OnComponentBeginOverlap.AddDynamic(this, &AEndLevelTriggerActor::OnBoxBeginOverlap);
}


// Called every frame
void AEndLevelTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndLevelTriggerActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (_boxCollider)
		_boxCollider->OnComponentBeginOverlap.RemoveAll(this);

	UGameplayStatics::OpenLevel(GetWorld(), FName(*nextLvl));
}

