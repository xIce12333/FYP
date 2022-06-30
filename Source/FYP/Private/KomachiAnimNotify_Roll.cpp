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
				Player->bUseControllerRotationYaw = false;
				Player->GetCharacterMovement()->MaxWalkSpeed = Player->KomachiState.RollSpeed;
				float x, y;
				Player->GetWorld()->GetFirstPlayerController()->GetInputAnalogStickState(EControllerAnalogStick::CAS_LeftStick, x, y);
				FVector Direction(y, x, 0);
				Player->SetActorRotation(Direction.Rotation());
				Player->LaunchCharacter(Direction * 4000, true, true); 
				return; 
			} 
			// finish rolling
			Player->bUseControllerRotationYaw = (Player->KomachiState.bIsStrafing)? true : false;
			Player->GetCharacterMovement()->MaxWalkSpeed = (Player->KomachiState.bIsStrafing)?  Player->KomachiState.StrafeSpeed : Player->KomachiState.WalkSpeed;
		}

	} 
	
}
