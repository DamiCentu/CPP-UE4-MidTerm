// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceFinal.generated.h"

/**
 * 
 */
UCLASS()
class DAMIANCENTURIONTP2_API UGameInstanceFinal : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
		int lives = 5;
	
	int playerSize = 1;
};
