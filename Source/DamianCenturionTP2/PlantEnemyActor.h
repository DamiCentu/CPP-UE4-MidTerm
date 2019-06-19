// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "PaperCharacterParcial.h"
#include "PlantEnemyActor.generated.h"

UCLASS()
class DAMIANCENTURIONTP2_API APlantEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		AActor* posOne;

	UPROPERTY(EditAnywhere)
		AActor* posTwo;
	
	UPROPERTY(EditAnywhere)
		float loopDelay = 0.0f;

	UPROPERTY(EditAnywhere)
		float startDelay = 2.0f;

	UPROPERTY(EditAnywhere)
		float speed = 200.0f;

private:
	void Move();

	AActor* _currentActor;

	bool _canMove;

	UBoxComponent * _boxCollider;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
