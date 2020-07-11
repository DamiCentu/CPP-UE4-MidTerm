// Fill out your copyright notice in the Description page of Project Settings.

#include "boundActor.h"
#include "OnHit.h"


// Sets default values
AboundActor::AboundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AboundActor::BeginPlay()
{
	Super::BeginPlay();
	_boxCollider = FindComponentByClass < UBoxComponent>();

	if (_boxCollider)
		_boxCollider->OnComponentBeginOverlap.AddDynamic(this, &AboundActor::OnBoxBeginOverlap);
}

// Called every frame
void AboundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AboundActor::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	IOnHit * hitActor = Cast<IOnHit>(OtherActor);
	if (hitActor) {
		hitActor->OnHit(true);
	}
}

