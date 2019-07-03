// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "OnHit.h"
#include "Engine/World.h"
#include "PaperCharacter.h"
#include "ConstructorHelpers.h"
#include "PaperFlipbookComponent.h"
#include "PlayerProjectile.h"
#include "TimerManager.h"
#include "PaperCharacterParcial.generated.h"

/**
 * 
 */
UCLASS()
class DAMIANCENTURIONTP2_API APaperCharacterParcial : public APaperCharacter , public IOnHit
{
	GENERATED_BODY()
	
public:
	float speed;
	UPROPERTY(VisibleAnywhere)
		UPaperFlipbookComponent* anim;

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* animIdle;

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* animRun;

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* animJump;

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* animIdleBig;

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* animRunBig;

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* animJumpBig;


	UPROPERTY(EditAnywhere)
		float jumpForce = 1000;

	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
		AActor* cameraMaxXPos;

	UPROPERTY(BlueprintReadOnly)
		AActor* cameraMinXPos;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float cameraZpositionOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float cameraXConstantPosOnLastLevel = 865;

	UPROPERTY(EditAnywhere)
		float impulseAfterKillingEnemy = 200;

	UPROPERTY(EditAnywhere)
		int maxSize = 2;

	UPROPERTY(EditAnywhere)
		float capsuleComponentSizeOnBig = 103;

	UPROPERTY(EditAnywhere)
		float capsuleComponentSizeOnSmall = 55;

	void AddImpulseAfterKillingEnemy(bool impulseSideWays = false);

	UPROPERTY(EditAnywhere)
		USoundWave* jumpClip;

	UPROPERTY(EditAnywhere)
		float shootLoopDelay = 2.0f;

	UPROPERTY(EditAnywhere)
		float shootStartDelay = 2.0f;

	UPROPERTY(EditAnywhere)
		float slowEffectLoopDelay = 2.0f;

	UPROPERTY(EditAnywhere)
		float slowEffectStartDelay = 2.0f;

	UPROPERTY(EditAnywhere)
		float offSetWhenGetsPowerUp = 30.0f;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<class APlayerProjectile> _playerProjectilConstructed;
		
	int size = 1;

	virtual void OnHit(bool instaKill = false) override;

	void SizeUp();

	UFUNCTION(BlueprintCallable)
		void SetJump();

	UFUNCTION(BlueprintCallable)
		void MyStopJump();

	UFUNCTION(BlueprintCallable)
		void Shoot();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int coins = 0;

private:
	TMap<FString, UPaperFlipbook*> anims;

	float _speedScale = 1.0;

	bool _canShoot = true;

	UCapsuleComponent * _capsuleCollider;

	void CanShootAgain();
	void ResetSpeed();
	void SetHorizontal(float h);

	UChildActorComponent* _fireSpawnPoint;
	

	void AddFlipbook(FString name, UPaperFlipbook * object);

	void ChangeAnimation(FString name);

	UAudioComponent* audioComp;

	const FString RUN_SMALL = "runSmall";
	const FString IDLE_SMALL = "idleSmall";
	const FString JUMP_SMALL = "jumpSmall";

	const FString RUN_BIG = "runBig";
	const FString IDLE_BIG = "idleBig";
	const FString JUMP_BIG= "jumpBig";
	
	
};
