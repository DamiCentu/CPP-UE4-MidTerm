// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/HUD.h"
#include "Engine/World.h"
#include "HUDParcial.generated.h"

/**
 * 
 */
UCLASS()
class DAMIANCENTURIONTP2_API AHUDParcial : public AHUD
{
	GENERATED_BODY()

public:
	AHUDParcial();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> hudWidget;

private:
	UUserWidget* _widget;
	
	
};
