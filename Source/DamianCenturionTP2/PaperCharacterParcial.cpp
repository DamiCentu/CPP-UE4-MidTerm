// Fill out your copyright notice in the Description page of Project Settings.

#include "PaperCharacterParcial.h"
#include "PaperFlipbook.h"

void APaperCharacterParcial::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;
	Super::BeginPlay();

	_fireSpawnPoint = FindComponentByClass<UChildActorComponent>();

	audioComp = FindComponentByClass<UAudioComponent>();
	if (audioComp)
	{
		audioComp->Stop();
	}

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
	else if (size >= 2 && _capsuleCollider)
	{
		float size = 0;
		float radius = 0;
		_capsuleCollider->GetUnscaledCapsuleSize(radius, size);
		_capsuleCollider->SetCapsuleSize(radius, capsuleComponentSizeOnBig);
	}


	SetActorLocation(FVector(GetActorLocation().X, 0, GetActorLocation().Z));
	SetActorRotation(FRotator(0, 0, 0));
}

void APaperCharacterParcial::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Horizontal", this, &APaperCharacterParcial::SetHorizontal);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed ,this, &APaperCharacterParcial::SetJump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &APaperCharacterParcial::MyStopJump);
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APaperCharacterParcial::Shoot);
}

void APaperCharacterParcial::SetHorizontal(float h)
{
	speed = h > 0 ? 1 : h < 0  ? - 1 : 0;
	AddMovementInput(GetActorForwardVector(), speed * _speedScale);
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

		if (audioComp)
		{
			audioComp->Sound = jumpClip;
			audioComp->Play();
		}
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

void APaperCharacterParcial::OnHit(bool instaKill) {
	size--;

	_speedScale = 0.5;

	FTimerHandle timerHandle;

	GetWorldTimerManager().SetTimer(timerHandle, this, &APaperCharacterParcial::ResetSpeed, slowEffectStartDelay, false, slowEffectLoopDelay);

	if (size < 1 || instaKill)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*UGameplayStatics::GetCurrentLevelName(GetWorld())));
	}
}

void APaperCharacterParcial::SizeUp() {
	if (size == 1)
	{
		SetActorLocation(GetActorLocation() + GetActorUpVector() * offSetWhenGetsPowerUp);
	}
	if (size <= maxSize)
		size++;

	if (GetCharacterMovement()->IsMovingOnGround() && speed == 0 && anim->GetFlipbook() == animIdle && size >= 2)
	{
		ChangeAnimation(IDLE_BIG);
	}
}


void APaperCharacterParcial::AddImpulseAfterKillingEnemy(bool impulseSideWays) {
	if (impulseSideWays)
	{
		float forceX = 0;
		if (cameraXConstantPosOnLastLevel <= GetActorLocation().X)
		{
			forceX = -1;
		}
		else
		{
			forceX = 1;
		}
		LaunchCharacter(FVector(forceX  * impulseAfterKillingEnemy * 4, 0 , 1 * impulseAfterKillingEnemy), false, false);
	}
	else {
		LaunchCharacter(GetActorUpVector() * impulseAfterKillingEnemy, false, false);
	}
}


void APaperCharacterParcial::Shoot()
{
	if (size < 3)
		return;

	auto world = GetWorld();

	if (_playerProjectilConstructed && world)
	{
		FActorSpawnParameters params;
		params.Owner = this;
		APlayerProjectile* projectile = world->SpawnActor<APlayerProjectile>(_playerProjectilConstructed, _fireSpawnPoint->GetComponentLocation(), anim -> GetComponentRotation(), params);
		FVector direction = anim->GetComponentRotation().Vector() + GetActorUpVector() / 4;
		projectile->SetImpulse(direction);

		_canShoot = false;

		FTimerHandle timerHandle;

		GetWorldTimerManager().SetTimer(timerHandle, this, &APaperCharacterParcial::CanShootAgain, shootStartDelay, false, shootLoopDelay);
	}
}

void APaperCharacterParcial::CanShootAgain(){
	_canShoot = true;
}

void APaperCharacterParcial::ResetSpeed() {
	_speedScale = 1.0;
}





