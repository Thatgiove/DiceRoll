#include "CameraDirector.h"

#include "DiceRollGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

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
		GameMode->OpenDiceMiniGame.AddDynamic(this, &ACameraDirector::ChangeCamera);
	}
}


void ACameraDirector::ChangeCamera()
{
	const float SmoothBlendTime = 0.75f;
	
	/*Se presente la nuova camera mi muovo in transizione verso di essa;
	 *allo stesso modo mi assicuro che la l'attuale camera non sia quella
	 *del player controller
	 */
	if(DiceTableCamera)
	{
		/*TODO castare il main controller*/
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

		if (OurPlayerController && (OurPlayerController->GetViewTarget() != DiceTableCamera))
		{
			OurPlayerController->SetViewTargetWithBlend(DiceTableCamera, SmoothBlendTime);
		}
	}
}
