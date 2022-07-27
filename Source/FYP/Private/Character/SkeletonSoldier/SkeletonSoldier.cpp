// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkeletonSoldier/SkeletonSoldier.h"

ASkeletonSoldier::ASkeletonSoldier()
{
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), "AttackSocketRight");
}

void ASkeletonSoldier::StateAttack()
{
	if (bIsAttacking) return;
	const int RandomAttackChoice = FMath::RandRange(0, 0);
	if (RandomAttackChoice > 0)				// P(Strong attack) = 20%
	{
		Super::StateAttack();
		return;
	}
	// Strong Attack, no delay when it is strong attack
	SpawnStrongAttackEffect(true);
	bIsAttacking = true;
	if (AIController) AIController->StopMovement();
	FacePlayer();
	if (!M_StrongAttack) return;
	PlayAnimMontage(M_StrongAttack, 1.3);
}

