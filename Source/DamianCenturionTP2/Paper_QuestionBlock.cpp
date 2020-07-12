// Fill out your copyright notice in the Description page of Project Settings.

#include "Paper_QuestionBlock.h"
#include "PowerUpActor.h"
#include "PaperCharacterParcial.h"


APaper_QuestionBlock::APaper_QuestionBlock()
{
	_spriteComponent = GetRenderComponent();

#if WITH_EDITOR
	auto coinBPPrefab = ConstructorHelpers::FObjectFinder<UBlueprint>(TEXT("Blueprint'/Game/MyContent/Blueprints/BP_Coin.BP_Coin'"));
	if (coinBPPrefab.Object)
		coinPrefab = coinBPPrefab.Object->GeneratedClass;

	auto powerUp = ConstructorHelpers::FObjectFinder<UBlueprint>(TEXT("Blueprint'/Game/MyContent/Blueprints/BP_PowerUpActor.BP_PowerUpActor'"));
	if (powerUp.Object)
		_powerUpConstructed = powerUp.Object->GeneratedClass;
#endif

#if !WITH_EDITOR
	auto coinBPPrefab = ConstructorHelpers::FObjectFinder<UClass>(TEXT("Class'/Game/MyContent/Blueprints/BP_Coin.BP_Coin_C'"));
	if (coinBPPrefab.Object)
		coinPrefab = coinBPPrefab.Object;

	auto powerUp = ConstructorHelpers::FObjectFinder<UClass>(TEXT("Class'/Game/MyContent/Blueprints/BP_PowerUpActor.BP_PowerUpActor_C'"));
	if (powerUp.Object)
		_powerUpConstructed = powerUp.Object;
#endif

	auto sprite = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/MyContent/Sprites/Enviroment/SpriteSheetEnvironment_Enviroment_24.SpriteSheetEnvironment_Enviroment_24'"));

	if (_spriteComponent && sprite.Object)
		_spriteComponent->SetSprite(sprite.Object);
}

void APaper_QuestionBlock::BeginPlay()
{
	_boxCollider = FindComponentByClass<UBoxComponent>();

	if (_boxCollider)
		_boxCollider->OnComponentHit.AddDynamic(this, &APaper_QuestionBlock::OnBoxHit);


	_spawnPoint = Cast<UChildActorComponent>(GetComponentByClass(UChildActorComponent::StaticClass()));
}

void APaper_QuestionBlock::OnBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (!OtherActor->IsA<APaperCharacterParcial>()) {
		return;
	}

	auto world = GetWorld();

	if (spawnPowerUp != "none")
	{
		if (_powerUpConstructed && world)
		{
			FActorSpawnParameters params;
			params.Owner = this;
			world->SpawnActor<APowerUpActor>(_powerUpConstructed, _spawnPoint->GetComponentLocation(), _spawnPoint->GetComponentRotation(), params);
		}
		amountOfHits -= 10000;
	}
	else if (coinPrefab && world)
	{
		amountOfHits--;

		FActorSpawnParameters params;
		params.Owner = this;
		auto coin = world->SpawnActor<ACoin>(coinPrefab, this->GetTransform(), params);
		coin->SetCoinAfterHitted();

		APaperCharacterParcial* charac = Cast<APaperCharacterParcial>(UGameplayStatics::GetPlayerCharacter(world, 0));

		if (charac)
		{
			charac->coins++;
		}
	}

	if (amountOfHits > 0)
		return;

	if (_boxCollider)
		_boxCollider->OnComponentHit.RemoveAll(this);

	_spriteComponent->SetMobility(EComponentMobility::Stationary);
	_spriteComponent->SetSprite(usedBoxSprite);
	_spriteComponent->SetMobility(EComponentMobility::Movable);

}

