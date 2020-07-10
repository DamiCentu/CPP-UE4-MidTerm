// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMovaebleEnemy.h"
#include "MushActor.generated.h"

UCLASS()
class DAMIANCENTURIONTP2_API AMushActor : public ABaseMovaebleEnemy
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

private:
	
};
