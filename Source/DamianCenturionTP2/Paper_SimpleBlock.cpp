// Fill out your copyright notice in the Description page of Project Settings.

#include "Paper_SimpleBlock.h"
#include "ConstructorHelpers.h"
#include "BaseMovaebleEnemy.h"
#include "PowerUpActor.h"
#include "Engine/World.h"

APaper_SimpleBlock::APaper_SimpleBlock()
{
	_spriteComponent = GetRenderComponent();

	auto sprite = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/MyContent/Sprites/Enviroment/SpriteSheetEnvironment_Enviroment_2.SpriteSheetEnvironment_Enviroment_2'"));
	
	if (_spriteComponent && sprite.Object)
		_spriteComponent->SetSprite(sprite.Object);

#if WITH_EDITOR
	auto powerUp = ConstructorHelpers::FObjectFinder<UBlueprint>(TEXT("Blueprint'/Game/MyContent/Blueprints/BP_PowerUpActor.BP_PowerUpActor'")); 
	if (powerUp.Object)
		_powerUpConstructed = powerUp.Object->GeneratedClass;
#endif

#if !WITH_EDITOR
	auto powerUp2 = ConstructorHelpers::FObjectFinder<UClass>(TEXT("Class'/Game/MyContent/Blueprints/BP_PowerUpActor.BP_PowerUpActor_C'"));
	if (powerUp2.Object)
		_powerUpConstructed = powerUp2.Object;
#endif

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

	_spawnPoint = Cast<UChildActorComponent>(GetComponentByClass(UChildActorComponent::StaticClass()));
}

void APaper_SimpleBlock::OnBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (!OtherActor->IsA<APaperCharacterParcial>()) {
		return;
	}

	if (spawnPowerUp != "none")
	{
		auto world = GetWorld();

		if (_powerUpConstructed && world)
		{
			FActorSpawnParameters params;
			params.Owner = this;
			world->SpawnActor<APowerUpActor>(_powerUpConstructed, _spawnPoint->GetComponentLocation(), _spawnPoint->GetComponentRotation(), params);
		}
		
		if (_boxCollider)
			_boxCollider->OnComponentHit.RemoveAll(this);

		_spriteComponent->SetMobility(EComponentMobility::Stationary);
		_spriteComponent->SetSprite(usedBoxSprite);
		_spriteComponent->SetMobility(EComponentMobility::Movable);

		return;
	}

	TArray<AActor*> actors;

	_topBoxCollider->GetOverlappingActors(actors);

	for (int i = 0; i < actors.Num(); i++)
	{
		AActor* actor = actors[i];
		if (actor)
		{
			ABaseMovaebleEnemy* enemy = Cast<ABaseMovaebleEnemy>(actor);
			if (enemy)
			{
				enemy->OnHit();
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
	if (trigger)
		trigger->Destroy();
	Destroy();
}
