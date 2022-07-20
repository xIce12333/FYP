// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EnemyAnimNotify_AttackLaunch.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API UEnemyAnimNotify_AttackLaunch : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
