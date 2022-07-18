// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/KomachiAnimNotify_Guard.h"

void UKomachiAnimNotify_Guard::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (!Player) return;
		Player->bCanMove = false;
		Player->bCanAttack = false;
		Player->bIsGuarding = true;
		Player->bCanDealDamage = false;
	}
}

void UKomachiAnimNotify_Guard::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (!Player) return;

		if (!Player->bGuardPressed) Player->StopAnimMontage();

	}
}

void UKomachiAnimNotify_Guard::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (!Player) return;
		Player->bIsGuarding = false;
		Player->bCanMove = true;
		Player->bCanAttack = true;
		Player->StopGuard();
	}
}
