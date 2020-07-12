// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "PaperSpriteActor.h"
#include "Paper2DClasses.h"
#include "PaperSprite.h"
#include "DestructibleComponent.h"
#include "TimerManager.h"
#include "PaperCharacterParcial.h"
#include "Paper_SimpleBlock.generated.h"

/**
 * 
 */
UCLASS()
class DAMIANCENTURIONTP2_API APaper_SimpleBlock : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APaper_SimpleBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class ATriggerVolume * trigger;

	UPROPERTY(EditAnywhere)
		float radius = 50;
	UPROPERTY(EditAnywhere)
		float force = 50;
	UPROPERTY(EditAnywhere)
		float baseDamage = 50;

	UPROPERTY(EditAnywhere)
		float loopDelay = 0.0f;

	UPROPERTY(EditAnywhere)
		float startDelay = 2.0f;

	UPROPERTY(EditAnywhere)
		FString spawnPowerUp = "none";

	UPROPERTY(EditAnywhere)
		UPaperSprite* usedBoxSprite;

private:
	UPaperSpriteComponent* _spriteComponent;	

	UDestructibleComponent* _destructiveComponent;
	
	UFUNCTION()
		void OnBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UBoxComponent * _boxCollider;

	UBoxComponent * _topBoxCollider;

	void DestroyObject();

	TSubclassOf<class APowerUpActor> _powerUpConstructed;

	UChildActorComponent* _spawnPoint;
};
