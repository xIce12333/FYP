// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Komachi/KomachiAnimController.h"

UKomachiAnimController::UKomachiAnimController()
{

}

UKomachiAnimController::~UKomachiAnimController()
{
	
}

void UKomachiAnimController::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	const AActor* OwningActor = GetOwningActor();
	if (OwningActor == nullptr) return;
	const AMiraiKomachi* OwningCharacter = Cast<AMiraiKomachi>(OwningActor);
	if (OwningCharacter == nullptr) return;
	
	CheckMovement(OwningActor, OwningCharacter);
}

void UKomachiAnimController::CheckMovement(const AActor* OwningActor, const AMiraiKomachi* OwningCharacter)
{
	float Speed = OwningActor->GetVelocity().Size();
	if (OwningCharacter->GetCharacterMovement()->IsFalling())
	{
		AnimState.SetStateToFalse();
		AnimState.bIsFalling = true;
	}
	else if (Speed > OwningCharacter->WalkSpeed + 10)
	{
		AnimState.SetStateToFalse();
		AnimState.bIsRunning = true;
	}
	else if (Speed > 0)
	{
		AnimState.SetStateToFalse();
		AnimState.bIsWalking = true;
	}
	else
	{
		AnimState.SetStateToFalse();
		AnimState.bIdle = true;
	}
}


