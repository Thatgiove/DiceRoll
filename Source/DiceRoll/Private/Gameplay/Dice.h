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
	// Sets default values for this actor's properties
	ADice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Un vettore che è perpendicolare al piano*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category = "Default")
		class UArrowComponent* NormalPlaneVector;
	
	/*La mesh del dado*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Static Mesh")
		class UStaticMeshComponent* DiceMesh;
	
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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/*Funzione che ci dice se la mesh è ferma*/
	float DiceMeshVelocity();

	/*La faccia del dado */
	uint8 GetDiceFace();
	
	/*Funzione che ci dice se i vettori sono paralleli al NormalPlaneVector*/
	bool CalculateIfVectorAreParallel();
};
