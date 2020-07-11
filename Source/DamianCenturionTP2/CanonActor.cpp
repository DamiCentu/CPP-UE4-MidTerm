// Fill out your copyright notice in the Description page of Project Settings.

#include "CanonActor.h"
#include "ConstructorHelpers.h"
#include "PaperSprite.h"
#include "TimerManager.h"
#include "BossFireProjectile.h"
#include "Engine/World.h"

ACanonActor::ACanonActor()
{
	_spriteComponent = GetRenderComponent();

	auto sprite = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/MyContent/Sprites/Enemies/enemiesSheet__65.enemiesSheet__65'"));

	if (_spriteComponent && sprite.Object)
		_spriteComponent->SetSprite(sprite.Object);

#if WITH_EDITOR
	auto fireProjectil = ConstructorHelpers::FObjectFinder<UBlueprint>(TEXT("Blueprint'/Game/MyContent/Blueprints/BP_BossFireProjectile.BP_BossFireProjectile'"));
	if (fireProjectil.Object)
		_projectilConstructed = fireProjectil.Object->GeneratedClass;
#endif

#if !WITH_EDITOR
	auto fireProjectil = ConstructorHelpers::FObjectFinder<UClass>(TEXT("Class'/Game/MyContent/Blueprints/BP_BossFireProjectile.BP_BossFireProjectile_C'"));
	if (fireProjectil.Object)
		_projectilConstructed = fireProjectil.Object;
#endif
}

void ACanonActor::BeginPlay()
{
	Super::BeginPlay();

	_spawnPoint = Cast<UChildActorComponent>(GetComponentByClass(UChildActorComponent::StaticClass()));

	LoopShoot();
}

void ACanonActor::LoopShoot() {
	auto world = GetWorld();

	if (_projectilConstructed && world)
	{
		FActorSpawnParameters params;
		params.Owner = this;
		world->SpawnActor<ABossFireProjectile>(_projectilConstructed, _spawnPoint->GetComponentLocation(), _spawnPoint->GetComponentRotation(), params);
	}

	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, this, &ACanonActor::LoopShoot, loopDelay, false, startDelay);
}


