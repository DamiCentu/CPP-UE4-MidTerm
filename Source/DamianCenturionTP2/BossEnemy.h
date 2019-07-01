// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "OnHit.h"
#include "GameFramework/Actor.h"
#include "PaperCharacterParcial.h"
#include "ConstructorHelpers.h"
#include "PaperFlipbookComponent.h"
#include "BossFireProjectile.h"
#include "ParabolicProjectile.h"
#include "Engine/World.h"
#include "BossEnemy.generated.h"

UCLASS()
class DAMIANCENTURIONTP2_API ABossEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	UPROPERTY(EditAnywhere)
		float movementSpeed = 100;

	UPROPERTY(EditAnywhere)
		int hitsCanTake = 10;

	UPROPERTY(EditAnywhere)
		int quantityOfShotsFire = 3;

	UPROPERTY(EditAnywhere)
		int quantityOfShotsParabolics = 6;

	UPROPERTY(EditAnywhere)
		UBoxComponent * triggerBoxCollider;

	UPROPERTY(EditAnywhere)
		UBoxComponent * hitBoxCollider;

	UPROPERTY(EditAnywhere)
		float chaseLoopDelay = 2.0f;

	UPROPERTY(EditAnywhere)
		float chaseStartDelay = 2.0f;

	UPROPERTY(EditAnywhere)
		float fireProjectileLoopDelay = 1.0f;

	UPROPERTY(EditAnywhere)
		float fireProjectileStartDelay = 1.0f;

	UPROPERTY(EditAnywhere)
		float parabolicProjectileLoopDelay = 0.5f;

	UPROPERTY(EditAnywhere)
		float parabolicProjectileStartDelay = 0.5f;

private:

	UFUNCTION()
		void OnTopBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void CheckIfCollideWithPlayer(AActor * other);

	bool _chaseTimerSetted = false;

	bool _canChase = true;

	int _timesFireShooted = 0;
	int _timesParabolicShooted = 0;

	UChildActorComponent* _fireSpawnPoint;

	UChildActorComponent* _parabolicSpawnPoint;

	APaperCharacterParcial* _player;

	UPaperFlipbookComponent* _anim;

	TSubclassOf<class ABossFireProjectile> _fireProjectilConstructed;
	TSubclassOf<class AParabolicProjectile> _parabolicProjectilConstructed;

	void ChasePlayer(float deltaTime);
	void ShootParabolic();
	void ShootFire();

	void LoopFire();
	void LoopParabolic();
	
};
