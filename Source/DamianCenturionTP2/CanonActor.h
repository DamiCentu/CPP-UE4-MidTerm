// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "PaperSpriteActor.h"
#include "Paper2DClasses.h"
#include "CanonActor.generated.h"

/**
 * 
 */
UCLASS()
class DAMIANCENTURIONTP2_API ACanonActor : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	ACanonActor();
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float loopDelay = 0.01f;

	UPROPERTY(EditAnywhere)
		float startDelay = 2.0f;
	
private:

	UPaperSpriteComponent* _spriteComponent;

	TSubclassOf<class ABossFireProjectile> _projectilConstructed;

	UChildActorComponent* _spawnPoint;

	void LoopShoot();

};
