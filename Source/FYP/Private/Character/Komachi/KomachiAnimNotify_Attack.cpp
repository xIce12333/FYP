// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/KomachiAnimNotify_Attack.h"

#include <windowsx.h>

/*void UKomachiAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			if (Player->bCanMove)
				Player->bCanAttack = false;
			
			Player->bCanMove = !Player->bCanMove;
			Player->bUseControllerRotationYaw = (Player->bTargetLocked)? true : false;
		}
	}
} */

void UKomachiAnimNotify_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			Player->bCanMove = false;
			Player->bCanAttack = false;
		}
	}
}

void UKomachiAnimNotify_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			Player->bCanMove = true;
			Player->bCanDealDamage = false;
			Player->bCanAttack = true;
		}
	}
}
