// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/KomachiAnimNotify_PickUp.h"

void UKomachiAnimNotify_PickUp::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (!Player) return;
		Player->bCanMove = false;
		Player->bIsInvulnerable = true;
		Player->bCanPickItem = false;
		
	}
}

void UKomachiAnimNotify_PickUp::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (!Player) return;
		Player->bCanMove = true;
		Player->bIsInvulnerable = false;
		Player->bCanPickItem = true;
	}
}
