// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerParcial.generated.h"

/**
 * 
 */
UCLASS()
class DAMIANCENTURIONTP2_API APlayerControllerParcial : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget> widgetMenu;

	UUserWidget * menu;

	virtual void BeginPlay() override;

	void ShowMenu();
	void HideMenu();
	
};
