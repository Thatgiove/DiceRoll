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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Faces", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Face1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Faces", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Face2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Faces", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Face3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Faces", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Face4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Faces", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Face5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Faces", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Face6;

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

	/*Funzione che calcola la faccia del dado*/
	UFUNCTION() 
		int32 GetDiceFace();
};
