// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseClass/EnemyBase.h"
#include "GameFramework/Character.h"
#include "SkeletonController.generated.h"

UCLASS()
class FYP_API ASkeletonController : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkeletonController();

private:
	virtual void Attack() override;
};
