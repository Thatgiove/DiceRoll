// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DiceRollGameModeBase.generated.h"

/**
 *
 */
 /*Delegati che gestiscono eventi di apertura e chiusura del minigioco di dadi*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenDiceMiniGameSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseDiceMiniGameSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateScoreArraySignature);

UCLASS()
class DICEROLL_API ADiceRollGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Default")
		bool bCanPlayDiceGame;

	/*specifico per il camera director e HUD nel playerController*/
	UPROPERTY()
		FOpenDiceMiniGameSignature OpenDiceMiniGame;

	/*specifico per il camera director e HUD nel playerController*/
	UPROPERTY()
		FCloseDiceMiniGameSignature CloseDiceMiniGame;

	/*specifico per lo score HUD*/
	UPROPERTY()
		FCloseDiceMiniGameSignature UpdateScoreArray;

	/*Il numero totale dei dadi da lanciare*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int32 NumberOfDice = 3;

	/*La somma di tutte le facce*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int32 TotalDiceSum = 0;

	/*l'array contenente gli ultimi 6 lanci*/
	TArray<int32> DiceSumArray;

	/*Evento dal FrontEnd*/
	UFUNCTION()
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
