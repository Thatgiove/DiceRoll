// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiceSpawner.generated.h"

UCLASS()
class ADiceSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADiceSpawner();

	/*Per settare il Dice_BP*/
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ADice> DiceToSpawn;
	

	/*Creo i dadi in base al numero selezionato da giocatore*/
	UFUNCTION()
		void SpawnDice(int32 NumberOfDice);

};
