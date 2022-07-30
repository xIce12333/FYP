// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Komachi/MiraiKomachi.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class FYP_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LaunchSpeed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SurvivalTime = 8;

	FVector Direction;

	float TimeElapsed = 0;

	AMiraiKomachi* Player;

	void HandleGuarded();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage = 10;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* HitBox;

	UFUNCTION()
	virtual void HitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	
};


