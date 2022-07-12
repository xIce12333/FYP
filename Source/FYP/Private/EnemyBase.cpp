// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	ActiveState = EnemyState::IDLE;
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}


// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickStateMachine();
	
}


float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (!bCanTakeDamage) return 0;

	bCanTakeDamage = false;
	FTimerHandle DelayTimer;
	GetWorld()->GetTimerManager().SetTimer(DelayTimer, this, &AEnemyBase::ResetCanTakeDamage, 0.5); // prevent taking damage more than once
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	if (CurrentHealth <= 0)
	{
		ChangeState(EnemyState::DEAD);
	}
	UE_LOG(LogTemp, Warning, TEXT("Hit! HP: %f"), CurrentHealth);

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


#pragma region StateMachine

void AEnemyBase::TickStateMachine()	
{
	switch (ActiveState)
	{
	case EnemyState::IDLE:
		StateIdle();
		break;
	case EnemyState::CHASE:
		StateChase();
		break;
	case EnemyState::ATTACK:
		StateAttacK();
		break;
	case EnemyState::STUN:
		StateStun();
		break;
	case EnemyState::DEAD:
		StateDead();
		break;
	}
}

void AEnemyBase::ChangeState(const EnemyState NewState)
{
	if (ActiveState != EnemyState::DEAD)
	{
		ActiveState = NewState;
	}
	
}

void AEnemyBase::StateIdle()
{
	if (!Player) return;

	FVector PlayerDirection = Player->GetActorLocation() - GetActorLocation();
//	UE_LOG(LogTemp, Warning, TEXT("DOT: %s"), *PlayerDirection.GetSafeNormal().ToString());
//	float DotProduct = FVector::DotProduct(GetActorForwardVector(), PlayerDirection.GetSafeNormal());
//	UE_LOG(LogTemp, Warning, TEXT("DOT: %f"), DotProduct);
/*	if (FindDistance() <= ChaseRange)
	{
		PlayerLocked = true;
		ChangeState(EnemyState::CHASE);
	} */
}

void AEnemyBase::StateChase()
{
	if (FindDistance() < AttackeRange)
	{
		ChangeState(EnemyState::ATTACK);
	}
}

void AEnemyBase::StateAttacK()
{
}

void AEnemyBase::StateStun()
{
}

void AEnemyBase::StateDead()
{
	if (!GetCurrentMontage() && M_Die)
		PlayAnimMontage(M_Die);
//	if (GetCurrentMontage()->GetName() == "M")
}

void AEnemyBase::ResetCanTakeDamage()
{
	bCanTakeDamage = true;
}

float AEnemyBase::FindDistance() const
{
	if (!Player) return 0;
	return  FVector::Distance(GetActorLocation(), Player->GetActorLocation());
}

#pragma endregion StateMachine
