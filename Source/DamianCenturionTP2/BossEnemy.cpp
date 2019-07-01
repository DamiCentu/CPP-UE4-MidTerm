// Fill out your copyright notice in the Description page of Project Settings.

#include "BossEnemy.h"


// Sets default values
ABossEnemy::ABossEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


#if WITH_EDITOR
	auto fireProjectil = ConstructorHelpers::FObjectFinder<UBlueprint>(TEXT("Blueprint'/Game/MyContent/Blueprints/BP_BossFireProjectile.BP_BossFireProjectile'"));
	if (fireProjectil.Object)
		_fireProjectilConstructed = fireProjectil.Object->GeneratedClass;

	auto parabolicProjectil = ConstructorHelpers::FObjectFinder<UBlueprint>(TEXT("Blueprint'/Game/MyContent/Blueprints/BP_ParabolicProjectile.BP_ParabolicProjectile'"));
	if (parabolicProjectil.Object)
		_parabolicProjectilConstructed = parabolicProjectil.Object->GeneratedClass;
#endif

#if !WITH_EDITOR
	auto fireProjectil = ConstructorHelpers::FObjectFinder<UClass>(TEXT("Class'/Game/MyContent/Blueprints/BP_BossFireProjectile.BP_BossFireProjectile_C'"));
	if (fireProjectil.Object)
		_fireProjectilConstructed = fireProjectil.Object;

	auto parabolicProjectil = ConstructorHelpers::FObjectFinder<UClass>(TEXT("Class'/Game/MyContent/Blueprints/BP_ParabolicProjectile.BP_ParabolicProjectile_C'"));
	if (parabolicProjectil.Object)
		_parabolicProjectilConstructed = parabolicProjectil.Object;
#endif
}

// Called when the game starts or when spawned
void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();


	_player = Cast<APaperCharacterParcial>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	_anim = FindComponentByClass<UPaperFlipbookComponent>();

	TArray<UBoxComponent*> boxes;
	GetComponents<UBoxComponent>(boxes);

	for (int i = 0; i < boxes.Num(); i++)
	{
		UBoxComponent* box = boxes[i];

		if (!box)
			continue;

		if (box->GetName() == "TriggerBox")
		{
			triggerBoxCollider = box;
		}
		else if (box->GetName() == "HitBox")
		{
			hitBoxCollider = box;
		}
	}

	TArray<UChildActorComponent*> childActors;
	GetComponents<UChildActorComponent>(childActors);

	for (int i = 0; i < childActors.Num(); i++)
	{
		UChildActorComponent* actorr = childActors[i];

		if (!actorr)
			continue;

		if (actorr->GetName() == "FireSpawnPoint")
		{
			_fireSpawnPoint = actorr;
		}
		else if (actorr->GetName() == "ParabolicSpawnPoint")
		{
			_parabolicSpawnPoint = actorr;
		}
	}


	if (triggerBoxCollider)
		triggerBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemy::OnBoxBeginOverlap);

	if (hitBoxCollider)
		hitBoxCollider->OnComponentHit.AddDynamic(this, &ABossEnemy::OnTopBoxHit);
	
}

// Called every frame
void ABossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!_player) return;

	if (_player->GetActorLocation().X < GetActorLocation().X)
	{
		SetActorRotation(FRotator(0, 180, 0));	
	}
	else
	{
		SetActorRotation(FRotator(0, 0, 0));
	}

	if(_canChase)
	{
		ChasePlayer(DeltaTime);
	}
}

void ABossEnemy::ChasePlayer(float deltaTime)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * movementSpeed * deltaTime);
	if (!_chaseTimerSetted)
	{
		_chaseTimerSetted = true;
		FTimerHandle timerHandle;
		float rand = FMath::RandRange(-1.0f, 1.0f);
		if (rand <= 0) {
			GetWorldTimerManager().SetTimer(timerHandle, this, &ABossEnemy::ShootFire, chaseStartDelay, false, chaseLoopDelay);
		}
		else
		{
			GetWorldTimerManager().SetTimer(timerHandle, this, &ABossEnemy::ShootParabolic, chaseStartDelay, false, chaseLoopDelay);
		}
	}
}

void ABossEnemy::ShootParabolic()
{
	_canChase = true;
	_chaseTimerSetted = false;

	_canChase = false;
	auto time = parabolicProjectileLoopDelay;
	for (int i = 0; i < quantityOfShotsParabolics; i++)
	{
		FTimerHandle timerHandle;
		GetWorldTimerManager().SetTimer(timerHandle, this, &ABossEnemy::LoopParabolic, parabolicProjectileStartDelay, false, time);

		time += parabolicProjectileLoopDelay;
	}
}

void ABossEnemy::LoopParabolic() {
	auto world = GetWorld();

	if (_fireProjectilConstructed && world)
	{
		FActorSpawnParameters params;
		params.Owner = this;
		FVector direction = GetActorRotation().Vector() + GetActorUpVector();
		AParabolicProjectile* projectile = world->SpawnActor<AParabolicProjectile>(_parabolicProjectilConstructed, _parabolicSpawnPoint->GetComponentLocation(), FRotator(0,0,0) /*FRotator(rotation.X, rotation.Y, rotation.Z)*/, params);

		_timesParabolicShooted++;

		projectile->SetImpulse(direction, _timesParabolicShooted);

		if (_timesParabolicShooted >= quantityOfShotsParabolics)
		{
			_timesParabolicShooted = 0;
			_chaseTimerSetted = false;
			_canChase = true;
		}
	}
}

void ABossEnemy::ShootFire()
{
	_canChase = false;
	auto time = fireProjectileLoopDelay;
	for (int i = 0; i < quantityOfShotsFire; i++)
	{
		FTimerHandle timerHandle;
		GetWorldTimerManager().SetTimer(timerHandle, this, &ABossEnemy::LoopFire, fireProjectileStartDelay, false, time);
		
		time += fireProjectileLoopDelay * 2;
	}
}

void ABossEnemy::LoopFire() {
	auto world = GetWorld();

	if (_fireProjectilConstructed && world)
	{
		FActorSpawnParameters params;
		params.Owner = this;
		world->SpawnActor<ABossFireProjectile>(_fireProjectilConstructed, _fireSpawnPoint->GetComponentLocation(), GetActorRotation(), params);
		_timesFireShooted++;

		if (_timesFireShooted >= quantityOfShotsFire)
		{
			_timesFireShooted = 0;
			_chaseTimerSetted = false;
			_canChase = true;
		}
	}
}

void ABossEnemy::OnTopBoxHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	hitsCanTake--;

	if (OtherActor->IsA<APaperCharacterParcial>()) {
		APaperCharacterParcial * charP = Cast<APaperCharacterParcial>(OtherActor);
		if (charP)
			charP->AddImpulseAfterKillingEnemy(true);
	}

	if (hitsCanTake > 0)
		return;

	//FTimerHandle timerHandle;
	//GetWorldTimerManager().SetTimer(timerHandle, this, &ABossEnemy::ShootParabolic, chaseStartDelay, false, chaseLoopDelay);

	UGameplayStatics::OpenLevel(GetWorld(), "Level1");
}

void ABossEnemy::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	CheckIfCollideWithPlayer(OtherActor);
}

void ABossEnemy::CheckIfCollideWithPlayer(AActor * other)
{
	IOnHit * hitActor = Cast<IOnHit>(other);
	if (hitActor) {
		hitActor->OnHit();
	}
}

