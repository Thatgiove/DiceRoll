// Fill out your copyright notice in the Description page of Project Settings.


#include "DiceSpawner.h"
#include "Components/StaticMeshComponent.h"
#include "Gameplay/Dice.h"
#include "Engine/World.h"
// Sets default values
ADiceSpawner::ADiceSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ADiceSpawner::SpawnDice(int32 NumberOfDice)
{

	FActorSpawnParameters SpawnInfo;
	/*todo controllare che ci siano dadi nel gioco poi chiamare CalculateDiceSum() in GameMode*/
	for (int i = 1; i <= NumberOfDice; i++)
	{
		if (DiceToSpawn)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				ADice* Dice = World->SpawnActor<ADice>(DiceToSpawn, GetActorLocation(), GetActorRotation(), SpawnInfo);
				/*Controlla che ci sia la mesh e che la simulazione fisica sia attiva*/
				if (Dice->DiceMesh && Dice->DiceMesh->IsSimulatingPhysics())
				{
					/*todo sistemare i valori*/
					/*Aggiunge un inpulso e un impulso angolare random*/
					Dice->DiceMesh->AddImpulse(FVector(1000.f, 1.f, 1.f));
					Dice->DiceMesh->AddAngularImpulseInRadians(FVector(0.f, 1000.f, 1.f));
				}
			}
		}
	}
}

