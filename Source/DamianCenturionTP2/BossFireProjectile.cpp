// Fill out your copyright notice in the Description page of Project Settings.

#include "BossFireProjectile.h"


// Sets default values
ABossFireProjectile::ABossFireProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABossFireProjectile::BeginPlay()
{
	Super::BeginPlay();

	_boxCollider = FindComponentByClass < UBoxComponent>();

	if (_boxCollider) {
		_boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABossFireProjectile::OnBoxBeginOverlap);
	}
}

// Called every frame
void ABossFireProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);
}

void ABossFireProjectile::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	IOnHit * hitActor = Cast<IOnHit>(OtherActor);
	if (hitActor) {
		hitActor->OnHit();
	}
	Destroy();
}


