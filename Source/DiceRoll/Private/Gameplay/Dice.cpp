// Fill out your copyright notice in the Description page of Project Settings.


#include "Dice.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"

ADice::ADice()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	DiceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dice StaticMesh"));
	DiceMesh->SetupAttachment(GetRootComponent());
	DiceMesh->SetSimulatePhysics(true);
	
	/*Creo un vettore ruotato si 90 sul pitch in modo che sia perpendicolare al piano*/
	NormalPlaneVector = CreateDefaultSubobject< UArrowComponent>(TEXT("Normal Plane Vector"));
	NormalPlaneVector->SetupAttachment(GetRootComponent());
	NormalPlaneVector->SetRelativeRotation(FRotator(90.f, 0, 0));
	NormalPlaneVector->SetRelativeLocation(FVector(0, 0, 0));
	NormalPlaneVector->ArrowColor = FColor::Green;

	/*Creo degli sceneComponent ruotati in modo tale da avere il vettore di
	 * Forward che punta sulla faccia del dado, aggiungo il component alla
	 * lista per poter in seguito fare i calcoli
	 */
	Face1 = CreateDefaultSubobject<USceneComponent>(TEXT("Face1"));
	Face1->SetupAttachment(DiceMesh);
	Face1->ComponentTags.Add(FName("1"));
	DiceFacesArray.Add(Face1);
	
	Face2 = CreateDefaultSubobject<USceneComponent>(TEXT("Face2"));
	Face2->SetupAttachment(DiceMesh);
	Face2->SetRelativeRotation(FRotator(-90.f, 0, 0));
	Face2->ComponentTags.Add(FName("2"));
	DiceFacesArray.Add(Face2);
	
	Face3 = CreateDefaultSubobject<USceneComponent>(TEXT("Face3"));
	Face3->SetupAttachment(DiceMesh);
	Face3->SetRelativeRotation(FRotator(0, 90, 0));
	Face3->ComponentTags.Add(FName("3"));
	DiceFacesArray.Add(Face3);
	
	Face4 = CreateDefaultSubobject<USceneComponent>(TEXT("Face4"));
	Face4->SetupAttachment(DiceMesh);
	Face4->SetRelativeRotation(FRotator(0, -90, 0));
	Face4->ComponentTags.Add(FName("4"));
	DiceFacesArray.Add(Face4);
	
	Face5 = CreateDefaultSubobject<USceneComponent>(TEXT("Face5"));
	Face5->SetupAttachment(DiceMesh);
	Face5->SetRelativeRotation(FRotator(90, 0, 0));
	Face5->ComponentTags.Add(FName("5"));
	DiceFacesArray.Add(Face5);
	
	Face6 = CreateDefaultSubobject<USceneComponent>(TEXT("Face6"));
	Face6->SetupAttachment(DiceMesh);
	Face6->SetRelativeRotation(FRotator(0, 180, 0));
	Face6->ComponentTags.Add(FName("6"));
	DiceFacesArray.Add(Face6);
}

// Called when the game starts or when spawned
void ADice::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ADice::CalculateIfVectorAreParallel()
{
	for (USceneComponent* Face : DiceFacesArray)
	{
		Face->GetForwardVector().Normalize();
		NormalPlaneVector->GetForwardVector().Normalize();
		
		FVector::DotProduct(UKismetMathLibrary::Normal(Face->GetForwardVector()), UKismetMathLibrary::Normal(NormalPlaneVector->GetForwardVector()));
	}
}