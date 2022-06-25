// Fill out your copyright notice in the Description page of Project Settings.


#include "KomachiAnimController.h"

UKomachiAnimController::UKomachiAnimController()
{
	
	AnimState.Add(TEXT("Idle"), true);
	AnimState.Add(TEXT("isWalking"), false);
	AnimState.Add(TEXT("isRunning"), false);
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
	if (Speed > OwningCharacter->WalkSpeed + 10)
		ChangeAnimationState(TEXT("isRunning"));
	else if (Speed > 0)
		ChangeAnimationState(TEXT("isWalking"));
	else
		ChangeAnimationState(TEXT("Idle"));
}

void UKomachiAnimController::ChangeAnimationState(const FString NewState)
{
	for (auto& State : AnimState)
	{
		State.Value = (State.Key == NewState) ? true : false;
	} 
}

