// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "PaperSpriteActor.h"
#include "ConstructorHelpers.h"
#include "Paper2DClasses.h"
#include "PaperSprite.h"
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

private:
	UPaperSpriteComponent* _spriteComponent;	

	//UDestructibleComponent* _destructiveComponent;
	
	UFUNCTION()
		void OnBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UBoxComponent * _boxCollider;
};
