// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Slime/Slime.h"

void ASlime::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASlime::StateAttack()
{
/*	if (FindPlayerDistance() > MeleeRange)
		ShootAttack();
	else
	{
		NormalAttack();
	} */
	if (bIsAttacking) return;
	if (AIController) AIController->StopMovement();
	bIsAttacking = true;
	FacePlayer();
	ShootAttack();
}

void ASlime::ShootAttack()
{
	if (!M_Shoot) return;
	UE_LOG(LogTemp, Warning, TEXT("play shoot"));
	PlayAnimMontage(M_Shoot);
}

void ASlime::NormalAttack()
{
	if (!M_Melee) return;
	PlayAnimMontage(M_Melee);
}

