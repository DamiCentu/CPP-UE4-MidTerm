// Fill out your copyright notice in the Description page of Project Settings.

#include "MushActor.h"


// Sets default values
AMushActor::AMushActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMushActor::BeginPlay()
{
	Super::BeginPlay();

	//_spriteComponent = GetRenderComponent();

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
	}

	if (leftBoxCollider)
		leftBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMushActor::OnLeftBoxBeginOverlap);

	if (topBoxCollider)
		topBoxCollider->OnComponentHit.AddDynamic(this, &AMushActor::OnTopBoxHit);

	if (rightBoxCollider)
		rightBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMushActor::OnRightBoxBeginOverlap);

	_onTriggerAction.AddDynamic(this, &AMushActor::CheckIfCollideWithPlayer);
}

// Called every frame
void AMushActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);
}

void AMushActor::OnTopBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (topBoxCollider)
		topBoxCollider->OnComponentHit.RemoveAll(this);

	if (OtherActor->IsA<APaperCharacterParcial>()) {
		APaperCharacterParcial * charP = Cast<APaperCharacterParcial>(OtherActor);
		if (charP)
			charP->AddImpulseAfterKillingEnemy();
	}

	Destroy();
}

void AMushActor::OnLeftBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<AMushActor>() || OtherActor->IsA<APaper_SimpleBlock>() || OtherActor->IsA<APowerUpActor>()) {
		return;
	}
	speed *= -1;
	_onTriggerAction.Broadcast(OtherActor);
}

void AMushActor::OnRightBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<AMushActor>() || OtherActor->IsA<APaper_SimpleBlock>()|| OtherActor->IsA<APowerUpActor>()) {
		return;
	}
	speed *= -1;
	_onTriggerAction.Broadcast(OtherActor);
}

void AMushActor::CheckIfCollideWithPlayer(AActor * other) {
		IOnHit * hitActor = Cast<IOnHit>(other);
		if (hitActor){
			hitActor->OnHit();
			Destroy();
		}
}

void AMushActor::OnHit(bool instaKill) {
	Destroy();
}


