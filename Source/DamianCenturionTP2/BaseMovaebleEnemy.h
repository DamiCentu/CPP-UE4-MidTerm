// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "OnHit.h"
#include "GameFramework/Actor.h"
#include "BaseMovaebleEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBaseHitCheck, AActor*, actor);

UCLASS()
class DAMIANCENTURIONTP2_API ABaseMovaebleEnemy : public AActor, public IOnHit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseMovaebleEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FBaseHitCheck _onTriggerAction;

	UFUNCTION()
		void OnTopBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnLeftBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnRightBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void HitActor(AActor * other);

	virtual bool ShouldChangeDirection(AActor * OtherActor);

	virtual void ChangeDirection();

	virtual void OnSideTriggers(AActor * OtherActor);

	virtual void OnTopTrigger(AActor * OtherActor);
	
	void CheckFall(float DeltaTime);

	UBoxComponent * leftBoxCollider;

	UBoxComponent * rightBoxCollider;

	UBoxComponent * topBoxCollider; 
		
	UBoxComponent * bottomBoxCollider;

	float _movementSpeed = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float speed = 500;

	UPROPERTY(EditAnywhere)
		float speedY = 400;

	UPROPERTY(EditAnywhere)
		float minLevel1Z = -1722;

	virtual void OnHit(bool instaKill = false) override;
	
};
