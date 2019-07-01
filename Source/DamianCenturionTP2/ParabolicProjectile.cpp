// Fill out your copyright notice in the Description page of Project Settings.

#include "ParabolicProjectile.h"


// Sets default values
AParabolicProjectile::AParabolicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParabolicProjectile::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AParabolicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParabolicProjectile::SetImpulse(FVector direction , int impulseMultiplier ) {

	_boxCollider = FindComponentByClass < UBoxComponent>();

	if (_boxCollider) {
		_boxCollider->OnComponentBeginOverlap.AddDynamic(this, &AParabolicProjectile::OnBoxBeginOverlap);
	}

	if (_boxCollider)
	{
		_boxCollider->AddImpulse(direction * force * impulseMultiplier / 1.5);
	}
}

void AParabolicProjectile::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<AParabolicProjectile>())
		return;

	IOnHit * hitActor = Cast<IOnHit>(OtherActor);
	if (hitActor) {
		hitActor->OnHit();
	}
	Destroy();
}

