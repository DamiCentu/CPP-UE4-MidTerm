// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "UObject/Interface.h"
#include "OnHit.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOnHit : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAMIANCENTURIONTP2_API IOnHit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void OnHit(bool instaKill = false);
	
};
