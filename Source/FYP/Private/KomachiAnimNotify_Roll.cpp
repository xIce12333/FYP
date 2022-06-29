// Fill out your copyright notice in the Description page of Project Settings.


#include "KomachiAnimNotify_Roll.h"

#include "Character/Komachi/MiraiKomachi.h"

void UKomachiAnimNotify_Roll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
//	UE_LOG(LogTemp, Warning, TEXT("Hi"));
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			Player->KomachiState.bCanMove = !Player->KomachiState.bCanMove;
			FString Str= Player->KomachiState.bCanMove? TEXT("true") : TEXT("false");
			UE_LOG(LogTemp, Warning, TEXT("Can Move: %s"), *Str);			
		}

	} 
	
}
