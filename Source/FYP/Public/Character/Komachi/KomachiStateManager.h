// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KomachiStateManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FKomachiStateManager
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		bool bIsFalling = false;
	UPROPERTY(BlueprintReadOnly)
		float WalkSpeed = 300;
	UPROPERTY(BlueprintReadOnly)
		float RunSpeed = 700;
	UPROPERTY(BlueprintReadOnly)
		float StrafeSpeed = 350;
	UPROPERTY(BlueprintReadOnly)
		float RollSpeed = 800;
	UPROPERTY(BlueprintReadWrite)
		bool bIsStrafing = false;
	UPROPERTY(BlueprintReadOnly)
		bool bCanMove = true;
	UPROPERTY(BlueprintReadOnly)
		bool bIsRolling = false;
	UPROPERTY(BlueprintReadOnly)
		bool bIsAttacking = false;
	UPROPERTY(BlueprintReadOnly)
		FVector RollVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<UAnimMontage*> M_Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Roll;

};


