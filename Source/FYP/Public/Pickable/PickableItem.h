// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Character/Komachi/MiraiKomachi.h"
#include "GameFramework/PlayerInput.h"
#include "PickableItem.generated.h"

UCLASS()
class FYP_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* SphereCollision;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBillboardComponent* PickUpIcon;

	APlayerController* PlayerController;

	AMiraiKomachi* Player;

	TArray<FInputActionKeyMapping> ActionMapping;
	
	virtual void GetPicked();
	
	bool bCanPick;
	bool bIsPicked;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
