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

	GetState(OwningActor, OwningCharacter);
//	CheckMovement(OwningActor, OwningCharacter);
	GetControll
}

void UKomachiAnimController::GetState(const AActor* OwningActor, const AMiraiKomachi* OwningCharacter)
{
	Speed = OwningActor->GetVelocity().Size();
	Direction = CalculateDirection(OwningActor->GetVelocity(), OwningActor->GetActorRotation());
	bIsStrafing = OwningCharacter->KomachiState.bIsStrafing;
	bIsFalling = OwningCharacter->KomachiState.bIsFalling;
}
void UKomachiAnimController::CheckMovement(const AActor* OwningActor, const AMiraiKomachi* OwningCharacter)
{
		
}

