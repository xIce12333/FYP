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
		UAnimMontage* M_Backstep;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Shoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")	
		float BackStepRange = 400;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")	
		float BackStepSpeed = 600;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SpawnMagicball();

	virtual void Tick(float DeltaSeconds) override;
	
	void ShootAttack();

	void HandleHitByMagicball();
private:
	virtual void StateAttack() override;
	
	void BackStep();
	
};
