// Fill out your copyright notice in the Description page of Project Settings.


#include "KomachiAnimNotify_Roll.h"

#include "Character/Komachi/MiraiKomachi.h"
#include "Kismet/GameplayStatics.h"

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
			if (!Player->KomachiState.bCanMove)	// rolling
			{
				Player->GetCharacterMovement()->MaxWalkSpeed = Player->KomachiState.RollSpeed;
	//			float x, y;
				if (!UGameplayStatics::GetPlayerController(GetWorld(), 0))
					UE_LOG(LogTemp, Warning, TEXT("Null"));
			//	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetInputAnalogStickState(EControllerAnalogStick::CAS_LeftStick, x, y);
		/*		FVector Direction(x, y, 0);
				Player->LaunchCharacter(Direction * 6000, true, true); */
				return;
			}
			// finish rolling

			Player->GetCharacterMovement()->MaxWalkSpeed = (Player->KomachiState.bIsStrafing)?  Player->KomachiState.StrafeSpeed : Player->KomachiState.WalkSpeed;
		}

	} 
	
}
