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
		bool bIdle = true;
	UPROPERTY(BlueprintReadOnly)
		bool bIsWalking = false;
	UPROPERTY(BlueprintReadOnly)
		bool bIsRunning = false;
	UPROPERTY(BlueprintReadOnly)
		bool bIsFalling = false;

	void SetStateToFalse();
};

inline void FKomachiStateManager::SetStateToFalse()
{
	bIdle = false;
	bIsWalking = false;
	bIsRunning = false;
	bIsFalling = false;
}

