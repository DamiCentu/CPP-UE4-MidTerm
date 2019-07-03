// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDParcial.h"
#include "Blueprint/UserWidget.h"


AHUDParcial::AHUDParcial()
{

}

void AHUDParcial::BeginPlay()
{
	Super::BeginPlay();

	if (hudWidget)
	{
		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Menu")
			return;

		_widget = CreateWidget<UUserWidget>(GetWorld(), hudWidget);

		if (_widget)
		{
			_widget->AddToViewport(widgetIndex);
		}
	}
}

void AHUDParcial::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHUDParcial::DrawHUD()
{
	Super::DrawHUD();
}

