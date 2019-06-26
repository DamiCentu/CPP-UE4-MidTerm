// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "PlayerControllerParcial.h" 
#include "UserWidgetParcial.generated.h"

/**
 * 
 */
UCLASS()
class DAMIANCENTURIONTP2_API UUserWidgetParcial : public UUserWidget
{
	GENERATED_BODY()
	
	
	UFUNCTION(BlueprintCallable)
		void ClickButtonForLoadLevel();
	
};
