// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"
#include "ConstructorHelpers.h"
#include "PaperCharacterParcial.h"
#include "PaperSpriteComponent.h"
#include "TimerManager.h"


// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto audioClip = ConstructorHelpers::FObjectFinder<USoundWave>(TEXT("SoundWave'/Game/MyContent/Sounds/Coin_Sound.Coin_Sound'"));

	if (audioClip.Object)
		coinClip = audioClip.Object;

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
	_sprite = FindComponentByClass<UPaperSpriteComponent>();

	_boxCollider = FindComponentByClass<UBoxComponent>();

	if (_boxCollider)
		_boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnBoxBeginOverlap);

	audioComp = FindComponentByClass<UAudioComponent>();
	if (audioComp && coinClip)
	{
		audioComp->Stop();
		audioComp->Sound = coinClip;
		audioComp->OnAudioFinished.AddDynamic(this, &ACoin::CallDestroy);
	}
}

void ACoin::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (_collected)
		return;

	if (OtherActor->IsA<APaperCharacterParcial>())
	{
		APaperCharacterParcial * charP = Cast<APaperCharacterParcial>(OtherActor);
		if (charP)
		{
			if (audioComp)
			{
				audioComp->Play();
			}

			DisableObject();

			charP->coins++;

			_collected = true;
		}
	}
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_canMove)
		SetActorLocation(GetActorLocation() + GetActorUpVector() * speed * DeltaTime);
}

void ACoin::SetCoinAfterHitted() {
	_canMove = true;
	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, this, &ACoin::DisableObject, startDelay, false, loopDelay);

	if (audioComp && coinClip)
	{
		audioComp->Stop();
		audioComp->Sound = coinClip;
		audioComp->Play();
	}
}

void ACoin::CallDestroy() {
	Destroy();
}

void ACoin::DisableObject() {
	if (_sprite)
		_sprite->SetVisibility(false);
}

