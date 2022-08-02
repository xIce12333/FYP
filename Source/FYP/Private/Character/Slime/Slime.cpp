// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Slime/Slime.h"

void ASlime::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASlime::StateAttack()
{
	if (bIsAttacking) return;
	if (AIController) AIController->StopMovement();
	UE_LOG(LogTemp, Warning, TEXT("Attack"));
	bIsAttacking = true;
	FacePlayer();
	if (FindPlayerDistance() < BackStepRange)		// Player is too close, backstep first and then shoot
	{
		BackStep();
		return;
	}
	// Player is far away, shoot directly
	const float StartAttackDelay = FMath::RandRange(StartAttackDelayMin, StartAttackDelayMax);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &ASlime::ShootAttack, StartAttackDelay);
}

void ASlime::ShootAttack()
{
	if (bIsStunning || bIsDead || !M_Shoot) return;
	PlayAnimMontage(M_Shoot, 0.5);
}

void ASlime::HandleHitByMagicball()
{
	if (!CheckStun()) return;
	// is stunning
	ChangeState(EnemyState::STUN);
}

void ASlime::BackStep()
{
	if (bIsStunning || bIsDead || !M_Backstep) return;
	PlayAnimMontage(M_Backstep);
}

