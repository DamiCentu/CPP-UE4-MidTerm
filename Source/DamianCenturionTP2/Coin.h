// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Coin.generated.h"

UCLASS()
class DAMIANCENTURIONTP2_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float loopDelay = 0.0f;

	UPROPERTY(EditAnywhere)
		float startDelay = 2.0f;

	UPROPERTY(EditAnywhere)
		float speed = 500.0f;

	void SetCoinAfterHitted();
	
private:
	bool _canMove = false;
	
	UFUNCTION()
		void CallDestroy();

	UFUNCTION()
		void DisableObject();

	UBoxComponent* _boxCollider;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UAudioComponent* audioComp;

	USoundWave* coinClip;

	class UPaperSpriteComponent* _sprite;

	bool _collected = false;
};
