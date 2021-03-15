// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DiceGameHUD.generated.h"

/*La Hud si interfaccia con la GameMode
 *per gesire gli eventi di click e per modificare
 *il numero di dadi
 */


UCLASS()
class UDiceGameHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	/*Bottone lancio dei dadi*/
	UPROPERTY(meta = (BindWidget))
		class UButton* RollDice;

	/*Bottone chiudi minigioco*/
	UPROPERTY(meta = (BindWidget))
		class UButton* CloseDiceGame;

	/*Aggiungi dado*/
	UPROPERTY(meta = (BindWidget))
		class UButton* AddDice;

	/*Rimuovi dado*/
	UPROPERTY(meta = (BindWidget))
		class UButton* RemoveDice;

	/*Ventical box degli ultimi 6 lanci*/
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UVerticalBox* ScoreBox;

	/*Menu dei diversi widget*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UUserWidget> ScoreWidget;

	/*Il Widget che userò in Game*/
	UPROPERTY()
		class UScoreHUD* ScoreHUD;
	
	/*Le funzioni chiamate dai bottoni*/
	UFUNCTION()
		void OnRollDice();

	UFUNCTION()
		void OnCloseDiceGame();

	UFUNCTION()
		void OnAddDice();

	UFUNCTION()
		void OnRemoveDice();

	/*La lista degli ultimi 6 lanci*/
	UFUNCTION()
		void UpdateScore();

private:

	UPROPERTY()
		class ADiceRollGameModeBase* GameMode;
};
