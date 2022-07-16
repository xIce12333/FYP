// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Combatant.generated.h"

UCLASS()
class ACombatant : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatant();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed")
		float WalkSpeed = 300;
	UPROPERTY(BlueprintReadOnly)
		bool bTargetLocked;
	UPROPERTY(BlueprintReadOnly)
		bool bIsDead;
	UPROPERTY(BlueprintReadOnly)
		bool bCanMove;
	UPROPERTY(BlueprintReadOnly)
		bool bCanDealDamage;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
		bool bIsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
		float MaxHealth = 30;
	UPROPERTY(BlueprintReadOnly)
		float CurrentHealth;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
