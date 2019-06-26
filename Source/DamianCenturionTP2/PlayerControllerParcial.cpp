// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerParcial.h"
#include "Blueprint/UserWidget.h"

void APlayerControllerParcial::BeginPlay()
{
	Super::BeginPlay();

	if (widgetMenu && !menu && UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Menu")
		menu = CreateWidget<UUserWidget>(this, widgetMenu);

	ShowMenu();
}

void APlayerControllerParcial::ShowMenu() {
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) != "Menu")
		return;

	if (menu && !menu->IsInViewport()) {
		menu->AddToViewport();

		bShowMouseCursor = true;
	}

}

void APlayerControllerParcial::HideMenu() {
	if (menu && menu->IsInViewport()) {
		bShowMouseCursor = false;
		menu->RemoveFromViewport();
	}
}

