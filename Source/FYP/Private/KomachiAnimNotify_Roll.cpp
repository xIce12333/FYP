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
			if (!Player->KomachiState.bCanMove)	// rolling
			{
				Player->GetCharacterMovement()->MaxWalkSpeed = Player->KomachiState.RollSpeed;
				float x, y;
				Player->GetWorld()->GetFirstPlayerController()->GetInputAnalogStickState(EControllerAnalogStick::CAS_LeftStick, x, y);
				UE_LOG(LogTemp, Warning, TEXT("X and Y: %f and %f"), x, y);
				const FVector Direction(y, x, 0);
				Player->LaunchCharacter(Direction * 4000, true, true); 
				return; 
			} 
			// finish rolling

			Player->GetCharacterMovement()->MaxWalkSpeed = (Player->KomachiState.bIsStrafing)?  Player->KomachiState.StrafeSpeed : Player->KomachiState.WalkSpeed;
		}

	} 
	
}
