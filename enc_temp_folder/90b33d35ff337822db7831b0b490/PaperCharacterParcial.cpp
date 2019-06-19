// Fill out your copyright notice in the Description page of Project Settings.

#include "PaperCharacterParcial.h"
#include "PaperFlipbook.h"

void APaperCharacterParcial::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;
	Super::BeginPlay();

	for (TActorIterator<AActor> actorItr(GetWorld()); actorItr; ++actorItr)
	{
		AActor * act = *actorItr;
		if (act && act->GetName() == "MaxCameraXPos")
			cameraMaxXPos = act;
		else if (act && act->GetName() == "MinCameraXPos")
			cameraMinXPos = act;
	}

	anim = FindComponentByClass<UPaperFlipbookComponent>();

	AddFlipbook(RUN_SMALL, animRun);
	AddFlipbook(IDLE_SMALL, animIdle);
	AddFlipbook(JUMP_SMALL, animJump);

	ChangeAnimation(JUMP_SMALL);
}

void APaperCharacterParcial::AddFlipbook(FString name, UPaperFlipbook * object)
{
	if(object && !anims.Contains(name))
		anims.Add(name, object);
}

void APaperCharacterParcial::ChangeAnimation(FString name)
{
	if (anims.Contains(name))
	{
		anim->SetRelativeScale3D(FVector(1, 1, 1));
		anim->SetFlipbook(anims[name]);
		anim->SetRelativeScale3D(FVector(6, 1, 6));
	}
}

void APaperCharacterParcial::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetCharacterMovement()->IsMovingOnGround() && speed == 0 && anim->GetFlipbook() != animIdle)
	{
		ChangeAnimation(IDLE_SMALL);
	}

	if (!GetCharacterMovement()->IsMovingOnGround() && (anim->GetFlipbook() == animIdle || anim->GetFlipbook() == animRun) && anim->GetFlipbook() != animJump) {
		ChangeAnimation(JUMP_SMALL);
	}

// 	if (_camera)
// 	{
// 		if (!cameraMinXPos || !cameraMaxXPos)
// 			return;
// 
// 		FTransform thisTransform = _camera->GetComponentTransform();
// 
// 		float posX = FMath::Clamp(thisTransform.GetLocation().X, cameraMinXPos->GetActorLocation().X, cameraMaxXPos->GetActorLocation().X);
// 
// 		thisTransform.SetLocation(FVector(posX, thisTransform.GetLocation().Y, cameraZpositionOffset));
// 	}
}

void APaperCharacterParcial::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Horizontal", this, &APaperCharacterParcial::SetHorizontal);
	PlayerInputComponent->BindAction("Jump", IE_Pressed ,this, &APaperCharacterParcial::SetJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APaperCharacterParcial::MyStopJump);
}

void APaperCharacterParcial::SetHorizontal(float h)
{
	speed = h > 0 ? 1 : h < 0  ? - 1 : 0;
	AddMovementInput(GetActorForwardVector(), speed);
	if (speed != 0)
	{
		if(GetCharacterMovement()->IsMovingOnGround())
			ChangeAnimation(RUN_SMALL);

		if (h < 0)
			anim->SetRelativeRotation(FRotator(0, 180, 0));
		else
			anim->SetRelativeRotation(FRotator(0, 0, 0));
	}
}

void APaperCharacterParcial::SetJump()
{
	if (GetCharacterMovement()->IsMovingOnGround()) {		
		bPressedJump = true;
		ChangeAnimation(JUMP_SMALL);
	}	
}

void APaperCharacterParcial::MyStopJump()
{
	bPressedJump = false;
}

void APaperCharacterParcial::OnHit() {
	UGameplayStatics::OpenLevel(GetWorld(), FName(*UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

void APaperCharacterParcial::AddImpulseAfterKillingEnemy() {
	GetCharacterMovement()->AddImpulse(GetActorUpVector() * impulseAfterKillingEnemy);
}



