// Fill out your copyright notice in the Description page of Project Settings.

#include "Paper_QuestionBlock.h"


APaper_QuestionBlock::APaper_QuestionBlock()
{
	_spriteComponent = GetRenderComponent();

	auto coinBPPrefab = ConstructorHelpers::FObjectFinder<UBlueprint>(TEXT("Blueprint'/Game/MyContent/Blueprints/BP_Coin.BP_Coin'"));

	if (coinBPPrefab.Object)
		coinPrefab = coinBPPrefab.Object->GeneratedClass;

	auto sprite = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/MyContent/Sprites/Enviroment/SpriteSheetEnvironment_Enviroment_24.SpriteSheetEnvironment_Enviroment_24'"));

	if (_spriteComponent && sprite.Object)
		_spriteComponent->SetSprite(sprite.Object);
}

void APaper_QuestionBlock::BeginPlay()
{
	_boxCollider = FindComponentByClass<UBoxComponent>();

	if (_boxCollider)
		_boxCollider->OnComponentHit.AddDynamic(this, &APaper_QuestionBlock::OnBoxHit);
}

void APaper_QuestionBlock::OnBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	amountOfHits--;

	auto world = GetWorld();

	if (coinPrefab && world)
	{
		FActorSpawnParameters params;
		params.Owner = this;
		auto coin = world->SpawnActor<ACoin>(coinPrefab, this->GetTransform(), params);
		coin->SetCoinAfterHitted();
	}

	if (amountOfHits > 0)
		return;

	if (_boxCollider)
		_boxCollider->OnComponentHit.RemoveAll(this);

	_spriteComponent->SetMobility(EComponentMobility::Stationary);
	_spriteComponent->SetSprite(usedBoxSprite);
	_spriteComponent->SetMobility(EComponentMobility::Movable);

}

