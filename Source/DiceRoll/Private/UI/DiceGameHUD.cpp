// Fill out your copyright notice in the Description page of Project Settings.

#include "DiceGameHUD.h"


#include "DiceRollGameModeBase.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/VerticalBox.h"
#include "Engine.h"

void UDiceGameHUD::NativeConstruct()
{
    Super::NativeConstruct();

    RollDice->OnClicked.AddDynamic(this, &UDiceGameHUD::OnRollDice);
}

void UDiceGameHUD::OnRollDice()
{
	if (ADiceRollGameModeBase* GameMode = Cast<ADiceRollGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->SpawnDiceAndCalculateSum();
	}
}