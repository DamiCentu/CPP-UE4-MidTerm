// Fill out your copyright notice in the Description page of Project Settings.

#include "PlantEnemyActor.h"


// Sets default values
APlantEnemyActor::APlantEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlantEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	if (posOne)
		_currentActor = posOne;

	_boxCollider = FindComponentByClass < UBoxComponent>();

	if (_boxCollider)
		_boxCollider->OnComponentBeginOverlap.AddDynamic(this, &APlantEnemyActor::OnBoxBeginOverlap);

	_canMove = true;
}

// Called every frame
void APlantEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_canMove && _currentActor) {
		FVector direction = _currentActor->GetActorLocation() - GetActorLocation();
		direction.Normalize(1);
		SetActorLocation(GetActorLocation() + direction * DeltaTime * speed);

		float distance = FVector::Dist(GetActorLocation(), _currentActor->GetActorLocation());

		if (distance < 10.0f)
		{
			FTimerHandle timerHandle;
			_canMove = false;
			GetWorldTimerManager().SetTimer(timerHandle, this, &APlantEnemyActor::Move, startDelay, false, loopDelay);
		}
	}	
}

void APlantEnemyActor::Move() {
	_canMove = true;
	if (!_currentActor || !posOne || !posTwo)  
	{
		return;
	}
	if (_currentActor == posOne)
	{
		_currentActor = posTwo;
	}
	else
	{
		_currentActor = posOne;
	}
}

void APlantEnemyActor::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	IOnHit * hitActor = Cast<IOnHit>(OtherActor);
	if (hitActor) {
		hitActor->OnHit();
	}
}

