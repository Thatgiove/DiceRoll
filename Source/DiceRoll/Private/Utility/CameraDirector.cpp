#include "CameraDirector.h"

#include "DiceRollGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MainPlayerController.h"

ACameraDirector::ACameraDirector()
{
	PrimaryActorTick.bCanEverTick = false;
}


void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
	/*Registro il metodo al delegato del GameMode*/
	if (ADiceRollGameModeBase* GameMode = Cast<ADiceRollGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OpenDiceMiniGame.AddDynamic(this, &ACameraDirector::CameraToTable);
		GameMode->CloseDiceMiniGame.AddDynamic(this, &ACameraDirector::CameraToPlayer);
	}
}

/*Dalla camera del player a quella del tavolo*/
void ACameraDirector::CameraToTable()
{
	const float SmoothBlendTime = 0.75f;
	
	/*Se presente la nuova camera mi muovo in transizione verso di essa;
	 *allo stesso modo mi assicuro che la l'attuale camera non sia quella
	 *del player controller
	 */
	if(DiceTableCamera)
	{
		AMainPlayerController* OurPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

		if (OurPlayerController && (OurPlayerController->GetViewTarget() != DiceTableCamera))
		{
			OurPlayerController->SetViewTargetWithBlend(DiceTableCamera, SmoothBlendTime);
		}
	}
}

/*Dalla camera del tavolo a quella del player*/
void ACameraDirector::CameraToPlayer()
{

}