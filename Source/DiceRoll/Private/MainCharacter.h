// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainCharacter | Component", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainCharacter | Component", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;
	
	/*Il riferimento al playerController*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MainCharacter | Controller") 
		class AMainPlayerController* MainPlayerController;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	
	void MoveForward(float Value);

	void MoveRight(float Value);

	void InvertedLookUp(float Rate);

	void StartSprint();

	void StopSprint();

	void Action();
};
