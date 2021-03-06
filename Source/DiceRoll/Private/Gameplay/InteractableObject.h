// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

UCLASS()
class AInteractableObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	
	virtual void BeginPlay() override;

	/*La mesh che il giocatore vede nel mondo di gioco*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh")
		class UStaticMeshComponent* ObjectMesh;

	/*La sfera di collisione interna  */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Collision")
		class USphereComponent* InternalSphereCollider;

	/*La sfera di collisione esterna */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Collision")
		class USphereComponent* ExternalSphereCollider;

	/*Un semplice testo che informa sull'azione da fare */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Info")
		class UTextRenderComponent* TextRender;

	/*Un serie di Material configurabili via Blueprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
		class UMaterial* DefaultMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
		class UMaterial* InternalMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
		class UMaterial* ExternalMaterial;

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
