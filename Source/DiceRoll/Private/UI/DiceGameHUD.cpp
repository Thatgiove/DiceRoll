// Fill out your copyright notice in the Description page of Project Settings.

#include "DiceGameHUD.h"


#include "DiceRollGameModeBase.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/VerticalBox.h"
#include "Engine.h"
#include "ScoreHUD.h"

void UDiceGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	GameMode = Cast<ADiceRollGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	RollDice->OnClicked.AddDynamic(this, &UDiceGameHUD::OnRollDice);
	CloseDiceGame->OnClicked.AddDynamic(this, &UDiceGameHUD::OnCloseDiceGame);

	AddDice->OnClicked.AddDynamic(this, &UDiceGameHUD::OnAddDice);
	RemoveDice->OnClicked.AddDynamic(this, &UDiceGameHUD::OnRemoveDice);

	/*Lanciato dalla gameMode una volta completati i calcoli*/
	GameMode->UpdateScoreArray.AddDynamic(this, &UDiceGameHUD::UpdateScore);
}

void UDiceGameHUD::OnRollDice()
{
	GameMode->SpawnDiceAndCalculateSum();
}

void UDiceGameHUD::OnCloseDiceGame()
{
	/*Scatta l'evento della chiusura del minigioco*/
	GameMode->CloseDiceMiniGame.Broadcast();
}

/*Funzioni per selezionare in numbero di Dadi*/
void UDiceGameHUD::OnAddDice()
{
	if (GameMode->NumberOfDice < 3)
		GameMode->NumberOfDice += 1;
}

void UDiceGameHUD::OnRemoveDice()
{
	if (GameMode->NumberOfDice > 1)
		GameMode->NumberOfDice -= 1;
}

/*Crea Un widget Score BP e lo assegna come figlo della vertical box*/
void UDiceGameHUD::UpdateScore()
{
	int32 LastSum = 0;
	
	if(GameMode->DiceSumArray.Num() > 0)
	{
		/*Prende l'ultimo elemento dell'array*/
		LastSum = GameMode->DiceSumArray.Last();
		
		if(ScoreWidget)
		{
			ScoreHUD = CreateWidget<UScoreHUD>(this, ScoreWidget);
			ScoreHUD->DisplayLastSum(LastSum);
			ScoreBox->AddChildToVerticalBox(ScoreHUD);
		}
		
	}
}