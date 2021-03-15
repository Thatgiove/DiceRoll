// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"

#include "DiceRollGameModeBase.h"
#include "UserWidget.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	/*Registro il metodo al delegato del GameMode*/
	if (ADiceRollGameModeBase* GameMode = Cast<ADiceRollGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		/*questo evento scatta quando il Pawn clicca sull'interactableObject*/
		GameMode->OpenDiceMiniGame.AddDynamic(this, &AMainPlayerController::ShowHUD);

		/*questo evento scatta al click del tasto close dell'HUD*/
		GameMode->CloseDiceMiniGame.AddDynamic(this, &AMainPlayerController::HideHud);
	}

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
	{
		DiceGameHud->SetVisibility(ESlateVisibility::Visible);
		
	}
	

	/*Disabilita l'input*/
	GetPawn()->DisableInput(this);
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

/*Nasconde il player HUD*/
void AMainPlayerController::HideHud()
{
	if (DiceGameHud)
		DiceGameHud->SetVisibility(ESlateVisibility::Hidden);

	/*Riabilita l'input*/
	GetPawn()->EnableInput(this);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}