// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemyAnimNotify_AttackLaunch.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API UEnemyAnimNotify_AttackLaunch : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
