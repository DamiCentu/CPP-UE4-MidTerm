// Fill out your copyright notice in the Description page of Project Settings.

#include "UserWidgetParcial.h"
#include "GameInstanceFinal.h"

void UUserWidgetParcial::ClickButtonForLoadLevel() {
	APlayerControllerParcial* controller = Cast<APlayerControllerParcial>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!controller)
		return;

	UGameInstanceFinal* gameInstance = Cast<UGameInstanceFinal>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(gameInstance)
		gameInstance->lives = 5;

	controller->HideMenu();
	UGameplayStatics::OpenLevel(GetWorld(), "Level1");
}
