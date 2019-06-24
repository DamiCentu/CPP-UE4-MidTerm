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

	if (_boxCollider)
		_boxCollider->OnComponentHit.AddDynamic(this, &APaper_SimpleBlock::OnBoxHit);
}

void APaper_SimpleBlock::OnBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (_boxCollider)
		_boxCollider->OnComponentHit.RemoveAll(this);
	Destroy();
}
