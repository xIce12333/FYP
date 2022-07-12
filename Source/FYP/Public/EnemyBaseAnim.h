// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyBaseAnim.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API UEnemyBaseAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	bool bIsDead;
};
