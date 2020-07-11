// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FrozeDebuffActor.generated.h"

UCLASS()
class DAMIANCENTURIONTP2_API AFrozeDebuffActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFrozeDebuffActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float timerInRateLoop= 0.01;

	UPROPERTY(EditAnywhere)
		float timerInFirstDelayLoop = 7;

	UPROPERTY(EditAnywhere)
		float speed = 500.0f;
	
private:

	void Reposition();

	FVector startPos;

	UBoxComponent * _boxCollider;
};
