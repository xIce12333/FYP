// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/KomachiAnimNotify_Attack.h"

#include <windowsx.h>

void UKomachiAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			if (Player->bCanMove)
				Player->bCanAttack = false;
			//TArray<> list = Player->GetAllChildActors();
			
			Player->bCanMove = !Player->bCanMove;
			Player->bUseControllerRotationYaw = (Player->bIsStrafing)? true : false;
		}
	}
}
