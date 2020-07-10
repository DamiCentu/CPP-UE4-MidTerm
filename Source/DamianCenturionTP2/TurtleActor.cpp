// Fill out your copyright notice in the Description page of Project Settings.

#include "TurtleActor.h"
#include "PaperCharacterParcial.h"
#include "TimerManager.h"

// Sets default values
ATurtleActor::ATurtleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurtleActor::BeginPlay()
{
	Super::BeginPlay();

	_flipBook = Cast<UPaperFlipbookComponent>(GetComponentByClass((UPaperFlipbookComponent::StaticClass())));	
	_animWalking = _flipBook->GetFlipbook();
}

// Called every frame
void ATurtleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurtleActor::ResetHit() {
	if (_sliding)
		return;

	_hitted = true;

	if(_animWalking)
		ChangeAnimation(_animWalking);

	_movementSpeed = speed;

	_flipBook->SetPlayRate(1);
}

void ATurtleActor::ResetPlayRateAnimation() {
	_flipBook->SetPlayRate(1);
}

void ATurtleActor::OnTopTrigger(AActor * OtherActor)
{
	if (OtherActor->IsA<APaperCharacterParcial>()) {
		APaperCharacterParcial * charP = Cast<APaperCharacterParcial>(OtherActor);
		if (charP)
			charP->AddImpulseAfterKillingEnemy();
	}

	if (_hitted && _sliding)
	{
		if (topBoxCollider)
			topBoxCollider->OnComponentHit.RemoveAll(this);

		Destroy();
	}

	if (_hitted && !_sliding)
	{
		_sliding = true;
		_movementSpeed = speedSliding;
	}

	if (!_hitted)
	{
		_hitted = true;
		if(animDying)
			ChangeAnimation(animDying);

		_flipBook->SetPlayRate(0);

		FTimerHandle timerHandle;

		FTimerHandle timerHandle2;

		GetWorldTimerManager().SetTimer(timerHandle2, this, &ATurtleActor::ResetPlayRateAnimation, 0, false, 3.5f);

		GetWorldTimerManager().SetTimer(timerHandle, this, &ATurtleActor::ResetHit, 0, false, 7);
		_movementSpeed = 0;
	}
}

void ATurtleActor::OnSideTriggers(AActor * OtherActor)
{
	if (!ShouldChangeDirection(OtherActor))
	{
		if (OtherActor->IsA<ABaseMovaebleEnemy>() && _hitted && _sliding)
			_onTriggerAction.Broadcast(OtherActor);

		return;
	}

	ChangeDirection();

	_onTriggerAction.Broadcast(OtherActor);
}

void ATurtleActor::HitActor(AActor * other) {
	IOnHit * hitActor = Cast<IOnHit>(other);
	if (hitActor) {
		hitActor->OnHit();
	}
}

void ATurtleActor::ChangeDirection()
{
	ABaseMovaebleEnemy::ChangeDirection();
	FVector scale = FVector(_flipBook->RelativeScale3D.X * -1, _flipBook->RelativeScale3D.Y, _flipBook->RelativeScale3D.Z);
	_flipBook->SetRelativeScale3D(scale);
}

void ATurtleActor::ChangeAnimation(UPaperFlipbook* flipbook)
{
	_flipBook->SetRelativeScale3D(FVector(1, 1, 1));
	_flipBook->SetFlipbook(flipbook);
	_flipBook->SetRelativeScale3D(FVector(6, 1, 6));
}

