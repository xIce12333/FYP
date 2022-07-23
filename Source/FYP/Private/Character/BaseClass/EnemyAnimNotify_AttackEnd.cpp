// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseClass/EnemyAnimNotify_AttackEnd.h"

#include "Character/BaseClass/EnemyBase.h"

void UEnemyAnimNotify_AttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(MeshComp->GetOwner());
		if (!Enemy) return;
		Enemy->AttackEnd();
	}
}
