// Fill out your copyright notice in the Description page of Project Settings.

#include "Paper_SimpleBlock.h"


APaper_SimpleBlock::APaper_SimpleBlock()
{
	_spriteComponent = GetRenderComponent();

	auto sprite = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/MyContent/Sprites/Enviroment/SpriteSheetEnvironment_Enviroment_2.SpriteSheetEnvironment_Enviroment_2'"));
	
	if (_spriteComponent && sprite.Object)
		_spriteComponent->SetSprite(sprite.Object);

}

void APaper_SimpleBlock::BeginPlay()
{
	_boxCollider = FindComponentByClass<UBoxComponent>();
	_destructiveComponent = FindComponentByClass<UDestructibleComponent>();

	TArray<UBoxComponent*> boxes;
	GetComponents<UBoxComponent>(boxes);

	for (int i = 0; i < boxes.Num(); i++)
	{
		UBoxComponent* box = boxes[i];

		if (!box)
			continue;

		if (box->GetName() == "TopBox")
		{
			_topBoxCollider = box;
		}
		else if (box->GetName() == "Box")
		{
			_boxCollider = box;
		}
	}


	if (_destructiveComponent)
		_destructiveComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (_boxCollider)
		_boxCollider->OnComponentHit.AddDynamic(this, &APaper_SimpleBlock::OnBoxHit);
}

void APaper_SimpleBlock::OnBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (!OtherActor->IsA<APaperCharacterParcial>()) {
		return;
	}

	//FHitResult hitResult;
	//FCollisionQueryParams queryParams = FCollisionQueryParams(
	//	FName(TEXT("")), //Esto es si lo quiero separar con un tag específico
	//	false, //Esto es si quiero obtener colisiones complejas
	//	this //Si quiero ignorar un actor en específico
	//);

	//GetWorld()->LineTraceSingleByObjectType(
	//	hitResult, //Donde saca el resultado
	//	GetActorLocation(), //De donde sale
	//	GetActorUpVector(), //A donde va
	//	FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
	//	queryParams
	//);

	//AActor* hitActor = hitResult.GetActor();

	//if (hitActor)
	//{
	//	AMushActor * mush = Cast<AMushActor>(hitActor);
	//	if (mush)
	//	{
	//		mush->OnHit();
	//	}
	//}

	TArray<AActor*> actors;

	_topBoxCollider->GetOverlappingActors(actors);

	for (int i = 0; i < actors.Num(); i++)
	{
		AActor* actor = actors[i];
		if (actor)
		{
			AMushActor* mush = Cast<AMushActor>(actor);
			if (mush)
			{
				mush->OnHit();
			}
		}
	}

	if (_boxCollider)
		_boxCollider->OnComponentHit.RemoveAll(this);

	_spriteComponent->SetVisibility(false);

	if (_destructiveComponent) {
		FVector aa = _destructiveComponent->GetComponentLocation();
		_destructiveComponent->ApplyRadiusDamage(baseDamage, aa, radius, force, true);

		FTimerHandle timerHandle;
		GetWorldTimerManager().SetTimer(timerHandle, this, &APaper_SimpleBlock::DestroyObject, startDelay, false, loopDelay);
	}
}

void APaper_SimpleBlock::DestroyObject() {
	Destroy();
}
