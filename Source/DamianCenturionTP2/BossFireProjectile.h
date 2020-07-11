// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "OnHit.h"
#include "PaperFlipbookComponent.h"
#include "BossFireProjectile.generated.h"

UCLASS()
class DAMIANCENTURIONTP2_API ABossFireProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossFireProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float speed = 200;

	UPROPERTY(EditAnywhere)
		UPaperFlipbook * bullet;

private:
	UBoxComponent * _boxCollider;


	UPaperFlipbookComponent * _flipBook;

	void ChangeAnimation(UPaperFlipbook* flipbook);

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
