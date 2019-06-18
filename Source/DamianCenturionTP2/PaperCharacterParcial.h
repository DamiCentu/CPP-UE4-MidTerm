// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "PaperCharacter.h"
#include "ConstructorHelpers.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacterParcial.generated.h"

/**
 * 
 */
UCLASS()
class DAMIANCENTURIONTP2_API APaperCharacterParcial : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	float speed;
	UPROPERTY(VisibleAnywhere)
		UPaperFlipbookComponent* anim;

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* animIdle;

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* animRun;

	UPROPERTY(EditAnywhere)
		UPaperFlipbook* animJump;


	UPROPERTY(EditAnywhere)
		float jumpForce = 1000;

	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
		AActor* cameraMaxXPos;

	UPROPERTY(BlueprintReadOnly)
		AActor* cameraMinXPos;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float cameraZpositionOffset;

// 	UPROPERTY(EditAnywhere)
// 		UCameraComponent* _camera;

	void OnHit();

private:
	TMap<FString, UPaperFlipbook*> anims;

	

	void SetHorizontal(float h);
	void SetJump();
	void MyStopJump();
	

	void AddFlipbook(FString name, UPaperFlipbook * object);

	void ChangeAnimation(FString name);

	

	const FString RUN_SMALL = "runSmall";
	const FString IDLE_SMALL = "idleSmall";
	const FString JUMP_SMALL = "jumpSmall";
	
	
};
