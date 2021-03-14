// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DiceGameHUD.generated.h"

/**
 *
 */
UCLASS()
class UDiceGameHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		class UButton* RollDice;

	UPROPERTY(meta = (BindWidget))
		class UButton* CloseDiceGame;

	UPROPERTY(meta = (BindWidget))
		class UButton* AddDice;
	
	UPROPERTY(meta = (BindWidget))
		class UButton* RemoveDice;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UVerticalBox* ScoreBox;
	
	UFUNCTION()
		void OnRollDice();
};
