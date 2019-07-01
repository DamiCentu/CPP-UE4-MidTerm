// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpActor.h"


// Sets default values
APowerUpActor::APowerUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerUpActor::BeginPlay()
{
	Super::BeginPlay();

	_boxCollider = FindComponentByClass < UBoxComponent>();

	if (_boxCollider) {
		_boxCollider->OnComponentBeginOverlap.AddDynamic(this, &APowerUpActor::OnBoxBeginOverlap);
		//_boxCollider->OnComponentEndOverlap.AddDynamic(this, &APowerUpActor::OnBoxEndOverlap);

	}
	
}

// Called every frame
void APowerUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);

	TArray<AActor*> actors;

	_boxCollider->GetOverlappingActors(actors);

	auto num = actors.Num();

	for (int i = 0; i < actors.Num(); i++)
	{
		AActor* actor = actors[i];
		if (actor && actor->IsA<APaper_SimpleBlock>())
		{
			num--;
		}
	}

	if(num <= 0)
		SetActorLocation(GetActorLocation() - GetActorUpVector()  * speedY * DeltaTime);

}

void APowerUpActor::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<AMushActor>() || OtherActor->IsA<APaper_SimpleBlock>()) {
		return;
	}

	speed *= -1;

	//_isOverlapping = true;

	if (OtherActor->IsA<APaperCharacterParcial>()) {
		APaperCharacterParcial * charP = Cast<APaperCharacterParcial>(OtherActor);
		if (charP)
		{
			Destroy();
			charP->SizeUp();
		}
	}

}

//void APowerUpActor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
//	_isOverlapping = false;
//}

