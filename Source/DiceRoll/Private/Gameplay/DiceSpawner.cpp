// Fill out your copyright notice in the Description page of Project Settings.

#include "DiceSpawner.h"
#include "DiceRollGameModeBase.h"
#include "Components/StaticMeshComponent.h"
#include "Gameplay/Dice.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


ADiceSpawner::ADiceSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADiceSpawner::SpawnDice(int32 NumberOfDice)
{
	/*info*/
	FActorSpawnParameters SpawnInfo;
	
	TArray<AActor*> DiceInWorld;

	UWorld* World = GetWorld();
	
	if (World)
	{
		/*Le Istanze dado nel mondo di gioco */
		UGameplayStatics::GetAllActorsOfClass(World, ADice::StaticClass(), DiceInWorld);

		/*Se esistono le distruggo*/
		if (DiceInWorld.Num() > 0)
		{
			for (auto dice : DiceInWorld)
			{
				World->DestroyActor(dice);
			}
			/*Richiamo questa stessa funzione*/
			SpawnDice(NumberOfDice);
		}
		/*Altimenti creo le istanze*/
		else
		{
			for (int i = 1; i <= NumberOfDice; i++)
			{
				if (DiceToSpawn)
				{
					/*Spawn dei dadi*/
					ADice* Dice = World->SpawnActor<ADice>(DiceToSpawn, GetActorLocation(), GetActorRotation(), SpawnInfo);

					/*Controlla che ci sia la mesh e che la simulazione fisica sia attiva*/
					if (Dice->DiceMesh && Dice->DiceMesh->IsSimulatingPhysics())
					{
						/*Randomizza i valori del vettore*/
						float RandomValue = FMath::RandRange(-500.f, 500.f);
						FVector RandomVector = FVector(RandomValue, RandomValue, RandomValue);

						/*Se il dado è solo 1 scala il vettore per avere un extra boost*/
						if (NumberOfDice == 1)
							RandomVector.X *= 10.f;
						
						/*Aggiunge un inpulso e un impulso angolare random*/
						Dice->DiceMesh->AddImpulse(RandomVector);
						Dice->DiceMesh->AddAngularImpulseInRadians(RandomVector);
						/*UE_LOG(LogTemp, Warning, TEXT("Text, %s "), *RandomVector.ToString());*/
					}

				}
			}
		}

	}
	
}

