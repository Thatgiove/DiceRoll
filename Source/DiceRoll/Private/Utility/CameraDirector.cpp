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
		/*questo evento scatta quando si preme il tasto azione nell'Interactable object*/
		GameMode->OpenDiceMiniGame.AddDynamic(this, &ACameraDirector::SwitchCamera);

		/*questo evento scatta al click del tasto close dell'HUD*/
		GameMode->CloseDiceMiniGame.AddDynamic(this, &ACameraDirector::SwitchCamera);
	}
}

/*Dalla camera del player a quella del tavolo*/
void ACameraDirector::SwitchCamera()
{
	const float SmoothBlendTime = 0.75f;
	
	/*Se presente la Camera sopra il tavolo da gioco mi muovo in transizione verso di essa;
	 *allo stesso modo mi assicuro che la l'attuale camera non sia quella
	 *del player controller; in caso contrario mi muovo verso il POV del Pawn
	 */
	if(DiceTableCamera)
	{
		AMainPlayerController* OurPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

		if (OurPlayerController && (OurPlayerController->GetViewTarget() != DiceTableCamera))
		{
			/*Dal Pawn alla camera*/
			OurPlayerController->SetViewTargetWithBlend(DiceTableCamera, SmoothBlendTime);
		}
		else
		{
			/*Dalla camera al Pawn*/
			OurPlayerController->SetViewTargetWithBlend(OurPlayerController->GetPawn(), SmoothBlendTime);
		}
	}
}

