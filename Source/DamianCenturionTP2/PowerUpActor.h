// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "ConstructorHelpers.h"
#include "Paper2DClasses.h"
#include "PaperSprite.h"
#include "PaperCharacterParcial.h"
#include "MushActor.h"
#include "Paper_SimpleBlock.h"
#include "PowerUpActor.generated.h"

UCLASS()
class DAMIANCENTURIONTP2_API APowerUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float speed = 500;

	UPROPERTY(EditAnywhere)
		float speedY = 50;

private:
	//bool _isOverlapping;

	UBoxComponent * _boxCollider;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);*/
	
};
