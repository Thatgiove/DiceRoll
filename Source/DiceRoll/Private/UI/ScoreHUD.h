// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreHUD.generated.h"

/**
 *
 */
UCLASS()
class UScoreHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	/*L'ultimo punteggio uscito dal lancio*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Score = 0;

	/*Assegna la somma alla variabile*/
	UFUNCTION()
		void DisplayLastSum(int32 LastSum);
};
