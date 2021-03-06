// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableObject.h"

#include "DiceRollGameModeBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "Materials/Material.h"


// Sets default values
AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = false;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	RootComponent = ObjectMesh;

	/*Creo la sphere collidre interna e lo attacco alla static mesh*/
	InternalSphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Internal Sphere Collision"));
	InternalSphereCollider->SetupAttachment(GetRootComponent());
	InternalSphereCollider->InitSphereRadius(120.f);

	/*Creo la sphere collidre esterno e lo attacco alla static mesh*/
	ExternalSphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("External Sphere Collision"));
	ExternalSphereCollider->SetupAttachment(GetRootComponent());
	ExternalSphereCollider->InitSphereRadius(500.f);

	/*Il tec*/
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));
	TextRender->SetupAttachment(GetRootComponent());
	TextRender->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	TextRender->SetVisibility(false);
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();

	InternalSphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AInteractableObject::OnComponentBeginOverlap);
	InternalSphereCollider->OnComponentEndOverlap.AddDynamic(this, &AInteractableObject::OnComponentEndOverlap);

	ExternalSphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AInteractableObject::OnComponentBeginOverlap);
	ExternalSphereCollider->OnComponentEndOverlap.AddDynamic(this, &AInteractableObject::OnComponentEndOverlap);
}

/*Questo metodo gestisce l'Overlap sia della sfera di collisione interna che quella esterna
 *Una volta Castato il PlayerCharacter cambia il Material ed è possibile cominciare a giocare al minigioco
 */
void AInteractableObject::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{

	if(Cast<ACharacter>(OtherActor))
	{
		if(OverlappedComponent == InternalSphereCollider)
		{
			if (ObjectMesh && InternalMaterial)
			{
				ObjectMesh->SetMaterial(0, InternalMaterial);

				if(TextRender) TextRender->SetVisibility(true);

				if (ADiceRollGameModeBase* GameMode = Cast<ADiceRollGameModeBase>(GetWorld()->GetAuthGameMode()))
				{
					GameMode->bCanPlayDiceGame = true;
					UE_LOG(LogTemp, Warning, TEXT("GameMode->bCanPlayDiceGame"));
				}
			}
		}
		else
		{
			if (ObjectMesh && ExternalMaterial)
			{
				ObjectMesh->SetMaterial(0, ExternalMaterial);
			}
		}
	}
}

void AInteractableObject::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex) 
{
	if (Cast<ACharacter>(OtherActor))
	{
		if (OverlappedComponent == InternalSphereCollider)
		{
			if (ObjectMesh && InternalMaterial)
			{
				ObjectMesh->SetMaterial(0, ExternalMaterial);

				if (TextRender) TextRender->SetVisibility(false);

				if (ADiceRollGameModeBase* GameMode = Cast<ADiceRollGameModeBase>(GetWorld()->GetAuthGameMode()))
				{
					GameMode->bCanPlayDiceGame = false;
				}
			}
		}
		else
		{
			if (ObjectMesh && ExternalMaterial)
			{
				ObjectMesh->SetMaterial(0, DefaultMaterial);
			}
		}
	}
}
