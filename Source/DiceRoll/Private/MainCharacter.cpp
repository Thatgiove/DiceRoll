// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	/*SpringArmComponent e proprietà*/
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeLocation(FVector(0, 30.f, 70.f));
	SpringArm->TargetArmLength = 127; 
	SpringArm->bEnableCameraLag = true; 
	SpringArm->CameraLagSpeed = 13.f;
	SpringArm->bUsePawnControlRotation = true; 
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	
	/*CameraComponent e proprietà*/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); 
	Camera->bUsePawnControlRotation = false;

	/*Configurazione CharacterMovement di base segue la direzione del character solamente quando esso è in movimento*/
	GetCharacterMovement()->bOrientRotationToMovement = false; 
	GetCharacterMovement()->bUseControllerDesiredRotation = false; 
	GetCharacterMovement()->RotationRate = FRotator(0, 360.f, 0);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*Se il player è fermo posso ruotare liberamente la camera*/
	if(UKismetMathLibrary::VSize(GetCharacterMovement()->Velocity) > 0.f)
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
	else
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
	}
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("Action"), IE_Pressed, this, &AMainCharacter::Action);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMainCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMainCharacter::StopSprint);

	//PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);
	//PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::MoveRight);

	//PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &AMainCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AMainCharacter::LookUpAtRate);
}

void AMainCharacter::Action() 
{
	UE_LOG(LogTemp, Warning, TEXT("Action"));
}
void AMainCharacter::StartSprint() 
{
	UE_LOG(LogTemp, Warning, TEXT("StartSprint"));
}
void AMainCharacter::StopSprint() 
{
	UE_LOG(LogTemp, Warning, TEXT("StopSprint"));
}

