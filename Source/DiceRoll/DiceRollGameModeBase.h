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

	/*Serve per il camera director*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable) /*todo UPROPERTY solo per test*/
		FOpenDiceMiniGameSignature OpenDiceMiniGame;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FCloseDiceMiniGameSignature CloseDiceMiniGame;/*todo UPROPERTY solo per test*/

	/*Il numero totale dei dadi da lanciare*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite) /*todo UPROPERTY solo per test*/
		int32 NumberOfDice = 3;

	/*La somma di tutte le facce*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite) /*todo UPROPERTY solo per test*/
		int32 TotalDiceSum = 0;

	/*l'array contenente gli ultimi 6 lanci*/
	TArray<int32> DiceSumArray;

	/*Evento dal FrontEnd*/
	UFUNCTION(BlueprintCallable) /*todo solo per test*/
		void SpawnDiceAndCalculateSum();

private:
	/*la velocità dei dadi sul tavolo da gioco*/
	UFUNCTION()
		void IsDiceVelocityZero(TArray<AActor*> DiceInWorld);

	/*calcolo la somma di tutte le facce dei dadi presenti nel mondo di gioco*/
	void CalculateDiceSum(TArray<AActor*> DiceInWorld);

	/*Aggiunge il risultato al DiceSumArray*/
	void AddSumToScoreArray(int32 Sum);
};
