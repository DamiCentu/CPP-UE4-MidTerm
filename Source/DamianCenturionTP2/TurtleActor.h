// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMovaebleEnemy.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "TurtleActor.generated.h"

UCLASS()
class DAMIANCENTURIONTP2_API ATurtleActor : public ABaseMovaebleEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurtleActor();

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* animDying;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ChangeDirection() override;

	virtual void OnSideTriggers(AActor * OtherActor) override;

	virtual void OnTopTrigger(AActor * OtherActor) override;

	virtual void HitActor(AActor * other) override;

    UPaperFlipbookComponent * _flipBook;

	UPaperFlipbook* _animWalking;

	

public:	
	// Called every frame
	UPROPERTY(EditAnywhere)
		float speedSliding = 500;

	virtual void Tick(float DeltaTime) override;	

private:
	void ChangeAnimation(UPaperFlipbook* flipbook);
	void ResetHit();
	void ResetPlayRateAnimation();

	bool _hitted = false;
	bool _sliding = false;

};
