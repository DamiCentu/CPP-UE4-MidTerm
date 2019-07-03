// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "PaperSpriteActor.h"
#include "ConstructorHelpers.h"
#include "Paper2DClasses.h"
#include "PaperSprite.h"
#include "Coin.h"
#include "PaperCharacterParcial.h"
#include "Engine/World.h"
#include "Paper_QuestionBlock.generated.h"

/**
 * 
 */
UCLASS()
class DAMIANCENTURIONTP2_API APaper_QuestionBlock : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APaper_QuestionBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPaperSpriteComponent* _spriteComponent;

	UFUNCTION()
		void OnBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UBoxComponent * _boxCollider;

public:

	UPROPERTY(EditAnywhere)
		int amountOfHits;

	UPROPERTY(EditAnywhere)
		UPaperSprite* usedBoxSprite;

	UPROPERTY(EditAnywhere)
		APaperCharacterParcial* character;

private:

	UAudioComponent* audioComp;

	USoundWave* coinClip;

	TSubclassOf<class ACoin> coinPrefab;	
};
