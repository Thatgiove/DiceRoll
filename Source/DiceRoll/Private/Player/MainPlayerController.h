// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 *
 */
UCLASS()
class AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	void ShowHUD();

	void HideHud();

protected:
	virtual void BeginPlay() override;

	/*Menu dei diversi widget*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UUserWidget> UserOverlayAsset;

	/*Il Widget che userò in Game*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		UUserWidget* DiceGameHud;


};
