// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"

#include "DiceRollGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
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
	if (UKismetMathLibrary::VSize(GetCharacterMovement()->Velocity) > 0.f)
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

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::MoveRight);

	/*Utilizzo il controller del APawn ad eccezione del pitch che ha il valore invertito*/
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMainCharacter::InvertedLookUp);
}

void AMainCharacter::MoveForward(float Value)
{
	/*trovo il forward in base alla rotation del controller*/
	const FRotator Rotation = GetControlRotation();
	/*nuovo rotator basato sulla rotazione del controller*/
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	/*Calcolo il valore di x nella matrice di rotazione indipendentemente dalla rotazione sullo Yaw /abbiamo il forward vector*/
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}


void AMainCharacter::MoveRight(float Value)
{
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction, Value);
}

/*Inverto il valore del pitch*/
void AMainCharacter::InvertedLookUp(float Rate)
{
	Super::AddControllerPitchInput(Rate * -1);
}

void AMainCharacter::Action()
{
	/*Chiamo l'evento di inizio del minigioco dei dadi. Questo evento avra un binding sulla level blueprint
	 *per gestire la logica di movimento della camera. TODO: tutto ciò verrà fatto da un Actor ACAmeraDirector
	 */
	if (ADiceRollGameModeBase* GameMode = Cast<ADiceRollGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		/*Chiamo l'evento di inizio gioco e non passo alcun parametro*/
		if (GameMode->bCanPlayDiceGame)
			GameMode->OpenDiceMiniGame.Broadcast();
	}
}

void AMainCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMainCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

