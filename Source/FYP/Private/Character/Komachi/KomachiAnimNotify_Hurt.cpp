// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/KomachiAnimNotify_Hurt.h"

void UKomachiAnimNotify_Hurt::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			Player->bCanMove = true;
		}
	}
}
