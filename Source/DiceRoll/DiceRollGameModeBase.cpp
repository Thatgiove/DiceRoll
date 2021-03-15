// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DiceRollGameModeBase.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Gameplay/Dice.h"
#include "Gameplay/DiceSpawner.h"
#include "Kismet/GameplayStatics.h"


void ADiceRollGameModeBase::SpawnDiceAndCalculateSum()
{
	/*Azzera la somma*/
	TotalDiceSum = 0;

	TArray<AActor*> DiceInWorld;

	UWorld* World = GetWorld();

	if (World)
	{
		/*Chiama il DiceSpawner e genera i dadi nel mondo*/
		ADiceSpawner* DiceSpawner = Cast<ADiceSpawner>(UGameplayStatics::GetActorOfClass(World, ADiceSpawner::StaticClass()));
		if (DiceSpawner)
			DiceSpawner->SpawnDice(NumberOfDice);

		/*Prendo tutti le istanze Dice presenti nel mondo di gioco*/
		UGameplayStatics::GetAllActorsOfClass(World, ADice::StaticClass(), DiceInWorld);

		/*Timer*/
		FTimerHandle TimerHandle;

		/*Delegato*/
		FTimerDelegate TimerDelegate;

		/*binding della funzione con parametri al timer*/
		TimerDelegate.BindUFunction(this, FName("IsDiceVelocityZero"), DiceInWorld);

		/*Chiama IsDiceVelocityZero in loop ogni secondo
		 *per verificare che tutti i dadi siano fermi*/
		World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, true);
	}
}

void ADiceRollGameModeBase::IsDiceVelocityZero(TArray<AActor*> DiceInWorld)
{
	/*Se solo un dado è fermo ritorna false*/
	for (auto dice : DiceInWorld)
	{
		ADice* Dice = Cast<ADice>(dice);
		if (Dice)
		{
			if (Dice->IsDiceStopped() == false)
				return;
		}
	}
	/*Se tutti i dadi sono fermi pulisce il timer
	 *e calcola la somma delle facce*/
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	CalculateDiceSum(DiceInWorld);
}

void ADiceRollGameModeBase::CalculateDiceSum(TArray<AActor*> DiceInWorld)
{
	for (auto dice : DiceInWorld)
	{
		ADice* Dice = Cast<ADice>(dice);
		TotalDiceSum += Dice->GetDiceFace();
	}
	AddSumToScoreArray(TotalDiceSum);
	/*UE_LOG(LogTemp, Warning, TEXT("SUM= %d "), TotalDiceSum);*/
}

/*Agginuge gli ultimi 6 lanci nella lista dei punteggi*/
void ADiceRollGameModeBase::AddSumToScoreArray(int32 Sum)
{
	if (DiceSumArray.Num() < 6)
	{
		DiceSumArray.Add(Sum);
		
		/*Questo evento viene intercettato dal HUD*/
		UpdateScoreArray.Broadcast();
	}
		

	
}