// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseClass/EnemyBase.h"
#include "SkeletonSoldier.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API ASkeletonSoldier : public AEnemyBase
{
	GENERATED_BODY()
public:
	ASkeletonSoldier();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class UStaticMeshComponent* Weapon;

	virtual void Attack() override;

};
