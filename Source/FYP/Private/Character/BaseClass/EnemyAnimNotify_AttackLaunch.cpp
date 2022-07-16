// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseClass/EnemyAnimNotify_AttackLaunch.h"

void UEnemyAnimNotify_AttackLaunch::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(MeshComp->GetOwner());
		if (Enemy)
		{
			const FVector ForwardDir = Enemy->GetActorRotation().Vector();
			Enemy->bCanDealDamage = true;
			Enemy->LaunchCharacter(ForwardDir * Enemy->AttackSpeed, true, true);
		}
	}
}
