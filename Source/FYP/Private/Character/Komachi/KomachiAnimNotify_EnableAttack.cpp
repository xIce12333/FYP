// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/KomachiAnimNotify_EnableAttack.h"

void UKomachiAnimNotify_EnableAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			Player->bCanAttack = true;
			const FVector ForwardDir = -Player->GetActorRotation().Vector();
			Player->LaunchCharacter(ForwardDir * Player->MeleeAttackSpeed, true, true);
		}
	} 
}
