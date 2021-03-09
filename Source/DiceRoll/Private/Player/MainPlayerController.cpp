// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "UserWidget.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UserOverlayAsset)
	{
		DiceGameHud = CreateWidget<UUserWidget>(this, UserOverlayAsset);
	}
	DiceGameHud->AddToViewport();
	DiceGameHud->SetVisibility(ESlateVisibility::Hidden);
}

void AMainPlayerController::ShowHUD()
{
	if (DiceGameHud)
		DiceGameHud->SetVisibility(ESlateVisibility::Visible);

	bShowMouseCursor = true;
}

void AMainPlayerController::HideHud()
{
	if (DiceGameHud)
		DiceGameHud->SetVisibility(ESlateVisibility::Hidden);

	bShowMouseCursor = false;
}