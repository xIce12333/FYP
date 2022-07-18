// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/KomachiAnimNotify_AttackLaunch.h"

/*void UKomachiAnimNotify_AttackLaunch::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			const FVector ForwardDir = Player->GetActorRotation().Vector();
			Player->bCanDealDamage = true;
			Player->LaunchCharacter(ForwardDir * Player->MeleeAttackSpeed, true, true);
		}
	}
} */

void UKomachiAnimNotify_AttackLaunch::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			const FVector ForwardDir = Player->GetActorRotation().Vector();
			Player->bCanDealDamage = true;
			Player->LaunchCharacter(ForwardDir * Player->MeleeAttackSpeed, true, true);
		}
	}
}

void UKomachiAnimNotify_AttackLaunch::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			Player->bCanAttack = true;
			Player->bCanDealDamage = false;
			const FVector BackwardDir = -Player->GetActorRotation().Vector();
			Player->LaunchCharacter(BackwardDir * Player->MeleeAttackSpeed, true, true);
		}
	}
}
