// Fill out your copyright notice in the Description page of Project Settings.

#include "UserWidgetParcial.h"

void UUserWidgetParcial::ClickButtonForLoadLevel() {
	APlayerControllerParcial* controller = Cast<APlayerControllerParcial>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!controller)
		return;

	controller->HideMenu();
	UGameplayStatics::OpenLevel(GetWorld(), "Level1");
}
