// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseClass/EnemyBase.h"
#include "SkeletonSoldier.generated.h"

class UNiagaraSystem;

/**
 * 
 */

UCLASS()
class FYP_API ASkeletonSoldier : public AEnemyBase
{
	GENERATED_BODY()
public:
	ASkeletonSoldier();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StrongAttackSpeed = 1000;
		
	UFUNCTION(BlueprintImplementableEvent)
	    void SpawnStrongAttackEffect(bool bShouldSpawn);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class UStaticMeshComponent* Weapon;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
//		UNiagaraSystem* StrongAttackEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_StrongAttack;
	

	virtual void StateAttack() override;
};
