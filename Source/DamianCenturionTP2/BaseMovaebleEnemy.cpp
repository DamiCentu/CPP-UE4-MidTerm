// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMovaebleEnemy.h"
#include "PaperCharacterParcial.h"
#include "Paper_SimpleBlock.h"
#include "PowerUpActor.h"
#include "TimerManager.h"
#include "Coin.h"
#include "Engine/World.h"

// Sets default values
ABaseMovaebleEnemy::ABaseMovaebleEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseMovaebleEnemy::BeginPlay()
{
	Super::BeginPlay();
	audioComp = FindComponentByClass<UAudioComponent>();
	_flipBook = Cast<UPaperFlipbookComponent>(GetComponentByClass((UPaperFlipbookComponent::StaticClass())));

	TArray<UBoxComponent*> boxes;
	GetComponents<UBoxComponent>(boxes);

	for (int i = 0; i < boxes.Num(); i++)
	{
		UBoxComponent* box = boxes[i];

		if (!box)
			continue;

		if (box->GetName() == "LeftBox")
		{
			leftBoxCollider = box;
		}
		else if (box->GetName() == "RightBox")
		{
			rightBoxCollider = box;
		}
		else if (box->GetName() == "TopBox")
		{
			topBoxCollider = box;
		}
		else if (box->GetName() == "BottomBox")
		{
			bottomBoxCollider = box;
		}
	}

	if (leftBoxCollider)
		leftBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseMovaebleEnemy::OnLeftBoxBeginOverlap);

	if (topBoxCollider)
		topBoxCollider->OnComponentHit.AddDynamic(this, &ABaseMovaebleEnemy::OnTopBoxHit);

	if (rightBoxCollider)
		rightBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseMovaebleEnemy::OnRightBoxBeginOverlap);

	_onTriggerAction.AddDynamic(this, &ABaseMovaebleEnemy::HitActor);
	
	_movementSpeed = speed;
}

// Called every frame
void ABaseMovaebleEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * _movementSpeed * DeltaTime);

	CheckFall(DeltaTime);
}

void ABaseMovaebleEnemy::CheckFall(float DeltaTime) {
	TArray<AActor*> actors;

	bottomBoxCollider->GetOverlappingActors(actors);

	auto num = actors.Num();

	for (int i = 0; i < actors.Num(); i++)
	{
		AActor* actor = actors[i];
		if (actor && actor->IsA<APaper_SimpleBlock>())
		{
			num--;
		}
	}

	if (num <= 0)
	{
		SetActorLocation(GetActorLocation() - GetActorUpVector()  * speedY * DeltaTime);

		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Level1")
		{
			if (GetActorLocation().Z < -1722)
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, minLevel1Z));
		}
		else if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Level2-2")
		{
			if (GetActorLocation().Z < -1722)
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, minLevel1Z));
		}
	}
}

void ABaseMovaebleEnemy::OnTopBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	OnTopTrigger(OtherActor);
}

void ABaseMovaebleEnemy::OnLeftBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OnSideTriggers(OtherActor);
}

void ABaseMovaebleEnemy::OnRightBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OnSideTriggers(OtherActor);
}

void ABaseMovaebleEnemy::OnTopTrigger(AActor * OtherActor)
{
	if (topBoxCollider)
		topBoxCollider->OnComponentHit.RemoveAll(this);

	if (rightBoxCollider)
		rightBoxCollider->OnComponentBeginOverlap.RemoveAll(this);

	if (leftBoxCollider)
		leftBoxCollider->OnComponentBeginOverlap.RemoveAll(this);

	if (OtherActor->IsA<APaperCharacterParcial>()) {
		APaperCharacterParcial * charP = Cast<APaperCharacterParcial>(OtherActor);
		if (charP)
			charP->AddImpulseAfterKillingEnemy();
	}

	if (audioComp)
	{
		audioComp->Play();
		FTimerHandle timerHandle;
		GetWorldTimerManager().SetTimer(timerHandle, this, &ABaseMovaebleEnemy::CallDestroy, 0.01, false, audioComp->Sound->Duration);
	}
	DisableObject();
}

void ABaseMovaebleEnemy::CallDestroy() {
	Destroy();
}

void ABaseMovaebleEnemy::DisableObject() {
	if (_flipBook)
		_flipBook->DestroyComponent(true);

	if (topBoxCollider)
		topBoxCollider->DestroyComponent(true);
}

void ABaseMovaebleEnemy::OnSideTriggers(AActor * OtherActor)
{
	if (!ShouldChangeDirection(OtherActor))
		return;

	ChangeDirection();

	_onTriggerAction.Broadcast(OtherActor);
}

void ABaseMovaebleEnemy::HitActor(AActor * other) {
	IOnHit * hitActor = Cast<IOnHit>(other);
	if (hitActor) {
		hitActor->OnHit();
		Destroy();
	}
}

void ABaseMovaebleEnemy::OnHit(bool instaKill) {
	Destroy();
}

bool ABaseMovaebleEnemy::ShouldChangeDirection(AActor * OtherActor) //child class must override
{
	if (OtherActor->IsA<ABaseMovaebleEnemy>() || OtherActor->IsA<APaper_SimpleBlock>() || OtherActor->IsA<APowerUpActor>() || OtherActor->IsA<ACoin>())
		return false;

	return true;
}

void ABaseMovaebleEnemy::ChangeDirection() {
	_movementSpeed *= -1;
}

