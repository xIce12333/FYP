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
		float StrafeSpeed = 200;
	UPROPERTY(BlueprintReadOnly)
		bool bIsStrafing = false;
};


