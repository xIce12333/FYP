// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/KomachiAnimNotify_Hurt.h"

void UKomachiAnimNotify_Hurt::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			UE_LOG(LogTemp,Warning,TEXT("Start"));
			Player->bCanMove = false;
			Player->bCanDealDamage = false;
			Player->bCanAttack = true;
			const FVector BackwardDir = -Player->GetActorRotation().Vector();
			Player->LaunchCharacter(BackwardDir * Player->KnockBackSpeed, true, true);
		}
	}

}

void UKomachiAnimNotify_Hurt::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			Player->bCanMove = true;
			Player->bCanGuard = true;
		}
	}
}
