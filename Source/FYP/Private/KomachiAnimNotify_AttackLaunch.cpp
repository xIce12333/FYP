// Fill out your copyright notice in the Description page of Project Settings.


#include "KomachiAnimNotify_AttackLaunch.h"

void UKomachiAnimNotify_AttackLaunch::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			const FVector ForwardDir = Player->GetActorRotation().Vector();
			Player->LaunchCharacter(ForwardDir * 1000, true, true);
		}
	}
}
