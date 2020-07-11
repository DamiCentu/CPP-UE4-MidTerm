// Fill out your copyright notice in the Description page of Project Settings.

#include "FrozeDebuffActor.h"
#include "TimerManager.h"
#include "PaperCharacterParcial.h"


// Sets default values
AFrozeDebuffActor::AFrozeDebuffActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFrozeDebuffActor::BeginPlay()
{
	Super::BeginPlay();

	_boxCollider = FindComponentByClass<UBoxComponent>();

	if (_boxCollider)
		_boxCollider->OnComponentBeginOverlap.AddDynamic(this, &AFrozeDebuffActor::OnBoxBeginOverlap);
	
	startPos = GetActorLocation();

	Reposition();
}

// Called every frame
void AFrozeDebuffActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorUpVector() * speed * DeltaTime);
}

void AFrozeDebuffActor::Reposition()
{
	SetActorLocation(startPos);

	FTimerHandle timerHandle;

	GetWorldTimerManager().SetTimer(timerHandle, this, &AFrozeDebuffActor::Reposition, timerInRateLoop, false, timerInFirstDelayLoop);
}

void AFrozeDebuffActor::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<APaperCharacterParcial>()) {
		APaperCharacterParcial * charP = Cast<APaperCharacterParcial>(OtherActor);
		if (charP)
			charP->FreezePlayer();
	}
}

