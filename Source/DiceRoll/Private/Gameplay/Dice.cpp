// Fill out your copyright notice in the Description page of Project Settings.


#include "Dice.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Math/Vector.h"

ADice::ADice()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsStopped = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	DiceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dice StaticMesh"));
	DiceMesh->SetupAttachment(GetRootComponent());
	DiceMesh->SetSimulatePhysics(true);

	/*Un vettore ruotato si 90 sul pitch in modo che sia perpendicolare al piano*/
	NormalPlaneVector = CreateDefaultSubobject< UArrowComponent>(TEXT("Normal Plane Vector"));
	NormalPlaneVector->SetupAttachment(GetRootComponent());
	NormalPlaneVector->SetRelativeRotation(FRotator(90.f, 0, 0));
	NormalPlaneVector->SetRelativeLocation(FVector(0, 0, 0));
	NormalPlaneVector->ArrowColor = FColor::Green;

	/*Creo 6 sceneComponent ruotati in modo tale da avere il vettore di
	 *Forward che punta sulla faccia del dado corrispondente, aggiungo il component alla
	 *lista per poter in seguito fare i calcoli
	 */
	USceneComponent* Face1 = CreateDefaultSubobject<USceneComponent>(TEXT("Face1"));
	Face1->SetupAttachment(DiceMesh);
	Face1->ComponentTags.Add(FName("1"));
	DiceFacesArray.Add(Face1);

	USceneComponent* Face2 = CreateDefaultSubobject<USceneComponent>(TEXT("Face2"));
	Face2->SetupAttachment(DiceMesh);
	Face2->SetRelativeRotation(FRotator(-90.f, 0, 0));
	Face2->ComponentTags.Add(FName("2"));
	DiceFacesArray.Add(Face2);

	USceneComponent*  Face3 = CreateDefaultSubobject<USceneComponent>(TEXT("Face3"));
	Face3->SetupAttachment(DiceMesh);
	Face3->SetRelativeRotation(FRotator(0, 90, 0));
	Face3->ComponentTags.Add(FName("3"));
	DiceFacesArray.Add(Face3);

	USceneComponent* Face4 = CreateDefaultSubobject<USceneComponent>(TEXT("Face4"));
	Face4->SetupAttachment(DiceMesh);
	Face4->SetRelativeRotation(FRotator(0, -90, 0));
	Face4->ComponentTags.Add(FName("4"));
	DiceFacesArray.Add(Face4);

	USceneComponent* Face5 = CreateDefaultSubobject<USceneComponent>(TEXT("Face5"));
	Face5->SetupAttachment(DiceMesh);
	Face5->SetRelativeRotation(FRotator(90, 0, 0));
	Face5->ComponentTags.Add(FName("5"));
	DiceFacesArray.Add(Face5);

	USceneComponent* Face6 = CreateDefaultSubobject<USceneComponent>(TEXT("Face6"));
	Face6->SetupAttachment(DiceMesh);
	Face6->SetRelativeRotation(FRotator(0, 180, 0));
	Face6->ComponentTags.Add(FName("6"));
	DiceFacesArray.Add(Face6);
}


int32 ADice::GetDiceFace()
{
	for (USceneComponent* Face : DiceFacesArray)
	{
		/*Verifico che i vettori di forward normalizzati della faccia del dado e del NormalPlaneVector siano paralleli*/
		if (FVector::DotProduct(Face->GetForwardVector(), NormalPlaneVector->GetForwardVector()) > 0.7f)
		{
			return UKismetStringLibrary::Conv_StringToInt(Face->ComponentTags[0].ToString());
		}
	}
	return 0;
}

/*Solo se la DiceMesh è ferma possiamo fare i calcoli*/
bool ADice::IsDiceStopped() 
{
	bIsStopped = DiceMesh && DiceMesh->IsSimulatingPhysics() && DiceMesh->GetComponentVelocity().Size() <= 0 ? true : false;
	return bIsStopped;
}