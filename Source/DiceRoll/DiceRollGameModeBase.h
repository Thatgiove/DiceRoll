// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DiceRollGameModeBase.generated.h"

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenDiceMiniGameSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseDiceMiniGameSignature);

UCLASS()
class DICEROLL_API ADiceRollGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Default")
		bool bCanPlayDiceGame;
	
	/*****TODO togliere BlueprintCallable*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FOpenDiceMiniGameSignature OpenDiceMiniGame;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FCloseDiceMiniGameSignature CloseDiceMiniGame;
	/*****TODO togliere BlueprintCallable*/
	
	int32 NumberOfDice;

	int32 TotalDiceSum;

private:
	/*l'array contenente gli ultimi 6 lanci*/
	TArray<int32> DiceSumArray;

	/*Per ogni dado presente nel mondo di gioco chiamo ricorsivamente questa
	 * funzione e mi assicuro che la velocità sia 0 prima di poter calcolare
	 * la somma*/
	bool IsDiceVelocityZero() const;

	/*calcolo la somma di tutte le facce dei dadi presenti nel mondo di gioco*/
	void CalculateDiceSum() const;

	/*Quando tutti i dadi sono fermi aggiungo il risultato al DiceSumArray*/
	void AddSumToScoreArray(int32 Sum);
};
