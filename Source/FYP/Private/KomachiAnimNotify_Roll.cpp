// Fill out your copyright notice in the Description page of Project Settings.


#include "KomachiAnimNotify_Roll.h"
#include "Kismet/GameplayStatics.h"

void UKomachiAnimNotify_Roll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AMiraiKomachi* Player = Cast<AMiraiKomachi>(MeshComp->GetOwner());
		if (Player)
		{
			Player->bCanMove = !Player->bCanMove;
			
			if (!Player->bCanMove)	// start rolling
				HandleBeginRolling(Player);
			else    // finish rolling
				HandleFinishRolling(Player);
		}
	} 
}

void UKomachiAnimNotify_Roll::HandleBeginRolling(AMiraiKomachi* Player)
{
	Player->bUseControllerRotationYaw = false;
	Player->GetCharacterMovement()->MaxWalkSpeed = Player->RollSpeed;
	float x, y;
	Player->GetWorld()->GetFirstPlayerController()->GetInputAnalogStickState(EControllerAnalogStick::CAS_LeftStick, y, x);
	
	const float ResultingYaw = FVector(x, y, 0).Rotation().Yaw + Player->GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Yaw;
	const FRotator Direction = FRotator(0, ResultingYaw, 0);
	Player->bIsRolling = true;
	Player->RollVec = Direction.Vector();
	Player->SetActorRotation(Direction);
}

void UKomachiAnimNotify_Roll::HandleFinishRolling(AMiraiKomachi* Player)
{
	Player->bUseControllerRotationYaw = (Player->bIsStrafing)? true : false;
	Player->bIsRolling = false;
	Player->GetCharacterMovement()->MaxWalkSpeed = (Player->bIsStrafing)?  Player->StrafeSpeed : Player->WalkSpeed;
}