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
	_capsuleCollider = FindComponentByClass<UCapsuleComponent>();

	AddFlipbook(RUN_SMALL, animRun);
	AddFlipbook(IDLE_SMALL, animIdle);
	AddFlipbook(JUMP_SMALL, animJump);
	AddFlipbook(RUN_BIG, animRunBig);
	AddFlipbook(IDLE_BIG, animIdleBig);
	AddFlipbook(JUMP_BIG, animJumpBig);

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
		if (size == 1) {
			ChangeAnimation(IDLE_SMALL);
		}
		else
		{
			ChangeAnimation(IDLE_BIG);
		}
	}

	if (!GetCharacterMovement()->IsMovingOnGround() && (anim->GetFlipbook() == animIdle || anim->GetFlipbook() == animRun) && anim->GetFlipbook() != animJump) {
		if (size == 1) {
			ChangeAnimation(JUMP_SMALL);
		}
		else 
		{
			ChangeAnimation(JUMP_BIG);
		}
	}

	if (size == 1 && _capsuleCollider)
	{
		float size = 0;
		float radius = 0;
		_capsuleCollider->GetUnscaledCapsuleSize(radius, size);
		_capsuleCollider->SetCapsuleSize(radius, capsuleComponentSizeOnSmall);
	}
	else if (size == 2 && _capsuleCollider)
	{
		float size = 0;
		float radius = 0;
		_capsuleCollider->GetUnscaledCapsuleSize(radius, size);
		_capsuleCollider->SetCapsuleSize(radius, capsuleComponentSizeOnBig);
	}

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
		if (GetCharacterMovement()->IsMovingOnGround()) {
			if (size == 1) {
				ChangeAnimation(RUN_SMALL);
			}
			else {
				ChangeAnimation(RUN_BIG);
			}
		}

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
		if (size == 1) {
			ChangeAnimation(JUMP_SMALL);
		}
		else
		{
			ChangeAnimation(JUMP_BIG);
		}
	}	
}

void APaperCharacterParcial::MyStopJump()
{
	bPressedJump = false;
}

void APaperCharacterParcial::OnHit() {
	size--;
	if (size < 1)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*UGameplayStatics::GetCurrentLevelName(GetWorld())));
	}
}

void APaperCharacterParcial::AddImpulseAfterKillingEnemy() {
	LaunchCharacter(GetActorUpVector() * impulseAfterKillingEnemy, false, false);
}



