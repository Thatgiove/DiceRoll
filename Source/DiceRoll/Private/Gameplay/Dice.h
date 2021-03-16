// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Actor.h"
#include "Dice.generated.h"

UCLASS()
class ADice : public AActor
{
	GENERATED_BODY()

public:

	ADice();
	UPROPERTY()
		bool bIsStopped = true;
protected:

	/*Un vettore che è perpendicolare al piano*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
		class UArrowComponent* NormalPlaneVector;

	/*L'array che contiene le facce dei dadi per fare le logiche di calcolo*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Faces")
		TArray<USceneComponent*> DiceFacesArray;

public:
	/*La mesh del dado*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh")
		class UStaticMeshComponent* DiceMesh;

	/*Funzione che ritorna la velocità della mesh*/
	UFUNCTION()
		bool IsDiceStopped();

	/*Calcola la faccia del dado*/
	UFUNCTION()
		int32 GetDiceFace();
};
