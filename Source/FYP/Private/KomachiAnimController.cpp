// Fill out your copyright notice in the Description page of Project Settings.


#include "KomachiAnimController.h"

UKomachiAnimController::UKomachiAnimController()
{
}

void UKomachiAnimController::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	AActor* OwningActor = GetOwningActor();
	if (OwningActor == nullptr)
		return;

	CheckMovement(OwningActor);
}

void UKomachiAnimController::CheckMovement(AActor* OwningActor)
{
	float Speed = OwningActor->GetVelocity().Size();
	
}

