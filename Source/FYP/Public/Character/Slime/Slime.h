// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseClass/EnemyBase.h"
#include "Slime.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API ASlime : public AEnemyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Melee;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Shoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")	
		float MeleeRange = 200;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SpawnMagicball();

	virtual void Tick(float DeltaSeconds) override;
private:
	virtual void StateAttack() override;

	void ShootAttack();
	void NormalAttack();
	
};
