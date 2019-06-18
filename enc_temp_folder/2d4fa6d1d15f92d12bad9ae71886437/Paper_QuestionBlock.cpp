// Fill out your copyright notice in the Description page of Project Settings.

#include "Paper_QuestionBlock.h"


APaper_QuestionBlock::APaper_QuestionBlock()
{
	_spriteComponent = GetRenderComponent();

	auto sprite = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/MyContent/Sprites/Enviroment/SpriteSheetEnvironment_Enviroment_24.SpriteSheetEnvironment_Enviroment_24'"));

	if (_spriteComponent && sprite.Object)
		_spriteComponent->SetSprite(sprite.Object);

	//RootComponent = _spriteComponent;
}

void APaper_QuestionBlock::BeginPlay()
{
	_boxCollider = FindComponentByClass<UBoxComponent>();

	if (_boxCollider)
		_boxCollider->OnComponentBeginOverlap.AddDynamic(this, &APaper_QuestionBlock::OnBoxBeginOverlap);
}

void APaper_QuestionBlock::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	amountOfHits--;
	if (amountOfHits >= 0)
		return;

	if (_boxCollider)
		_boxCollider->OnComponentBeginOverlap.RemoveAll(this);
	Destroy();
}

