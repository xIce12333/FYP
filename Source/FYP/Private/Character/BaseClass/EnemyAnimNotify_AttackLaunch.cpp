// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseClass/EnemyAnimNotify_AttackLaunch.h"


void UEnemyAnimNotify_AttackLaunch::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(MeshComp->GetOwner());
		if (!Enemy) return;
		const FVector ForwardDir = Enemy->GetActorRotation().Vector();
		Enemy->bCanDealDamage = true;
		Enemy->LaunchCharacter(ForwardDir * Enemy->AttackSpeed, true, true);
		
	}
}

void UEnemyAnimNotify_AttackLaunch::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(MeshComp->GetOwner());
	if (!Enemy) return;
	Enemy->bCanDealDamage = false;
}
