// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "OnHit.h"
#include "GameFramework/Actor.h"
#include "ConstructorHelpers.h"
#include "Paper2DClasses.h"
#include "PaperSprite.h"
#include "PaperCharacterParcial.h"
#include "Paper_SimpleBlock.h"
#include "PowerUpActor.h"
#include "MushActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitCheck, AActor*, actor);

UCLASS()
class DAMIANCENTURIONTP2_API AMushActor : public AActor, public IOnHit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMushActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float speed = 500;


	virtual void OnHit(bool instaKill = false) override;

private:
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FHitCheck _onTriggerAction;

	UPaperFlipbookComponent* _spriteComponent;

	UFUNCTION()
		void OnTopBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnLeftBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnRightBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void CheckIfCollideWithPlayer(AActor * other);

	UBoxComponent * leftBoxCollider;

	UBoxComponent * rightBoxCollider;

	UBoxComponent * topBoxCollider;
	
};
