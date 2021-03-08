/*Questa classe si occupa di gestire le camere;
 *In questo caso intercetta l'evento di inizio
 *del minigioco nel gamemode e cambia la camera dal player
 *a quella sopra il tavolo da gioco
 *
 */
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class ACameraDirector : public AActor
{
	GENERATED_BODY()

public:
	ACameraDirector();

protected:
	
	virtual void BeginPlay() override;

public:
	/*La camera da settare direttamente nell'istanza di questa classe*/
	UPROPERTY(EditAnywhere)
		AActor* DiceTableCamera;

	/*La funzione deve essere segnata come UFUNCTION per poter essere bindata*/
	UFUNCTION()
		void ChangeCamera();
};
