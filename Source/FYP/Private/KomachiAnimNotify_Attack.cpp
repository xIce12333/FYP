// Fill out your copyright notice in the Description page of Project Settings.


#include "KomachiAnimNotify_Attack.h"

void UKomachiAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			if (Player->bCanMove)
				Player->bCanAttack = false;
			Player->bCanMove = !Player->bCanMove;
		}
	}
}
