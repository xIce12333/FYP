// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Slime/SlimeAnimNotify_Backstep.h"

#include "Character/Slime/Slime.h"


void USlimeAnimNotify_Backstep::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                            float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ASlime* Enemy = Cast<ASlime>(MeshComp->GetOwner());
		if (!Enemy) return;
		BackStepDirection = -Enemy->GetActorForwardVector();
	} 
}

void USlimeAnimNotify_Backstep::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ASlime* Enemy = Cast<ASlime>(MeshComp->GetOwner());
		if (!Enemy) return;
		Enemy->GetCharacterMovement()->Velocity = BackStepDirection * Enemy->BackStepSpeed;
	} 
}

void USlimeAnimNotify_Backstep::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ASlime* Enemy = Cast<ASlime>(MeshComp->GetOwner());
		if (!Enemy) return;
		Enemy->ShootAttack();
	} 
}
