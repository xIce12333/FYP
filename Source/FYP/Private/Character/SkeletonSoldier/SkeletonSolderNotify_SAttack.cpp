// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkeletonSoldier/SkeletonSolderNotify_SAttack.h"

#include "Character/SkeletonSoldier/SkeletonSoldier.h"

void USkeletonSolderNotify_SAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ASkeletonSoldier* Enemy = Cast<ASkeletonSoldier>(MeshComp->GetOwner());
		if (!Enemy) return;
		AttackDirection = Enemy->GetActorRotation().Vector();
		Enemy->bCanDealDamage = true;
		Enemy->bIsStrongAttack = true; 
	}
}

void USkeletonSolderNotify_SAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ASkeletonSoldier* Enemy = Cast<ASkeletonSoldier>(MeshComp->GetOwner());
		if (!Enemy) return;
		Enemy->GetCharacterMovement()->Velocity = AttackDirection * Enemy->StrongAttackSpeed;
	}
}

void USkeletonSolderNotify_SAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ASkeletonSoldier* Enemy = Cast<ASkeletonSoldier>(MeshComp->GetOwner());
	if (!Enemy) return;
	Enemy->bCanDealDamage = false;
	Enemy->bIsStrongAttack = false;
	Enemy->SpawnStrongAttackEffect(false);
}
