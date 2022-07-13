// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;

	AttackHitBoxLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitBoxLeft"));
	AttackHitBoxLeft->SetupAttachment(GetMesh(), TEXT("HitboxSocketLeft"));
	AttackHitBoxRight = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitBoxRight"));
	AttackHitBoxRight->SetupAttachment(GetMesh(), TEXT("HitboxSocketRight"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	ActiveState = EnemyState::IDLE;
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AIController = Cast<AAIController>(GetController());
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
	if (bIsDead) return;
	
	switch (ActiveState)
	{
	case EnemyState::IDLE:
		StateIdle();
		break;
	case EnemyState::CHASE:
		StateChase();
		break;
	case EnemyState::ATTACK:
		StateAttack();
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

	const float PlayerDistance = FindPlayerDistance();
	if (PlayerDistance < AttackRange)
	{
		ChangeState(EnemyState::ATTACK);
	}
	else if (FindPlayerDistance() < ChaseRange)
	{
		ChangeState(EnemyState::CHASE);
	}
		
}

void AEnemyBase::StateChase()
{
	if (FindPlayerDistance() < AttackRange)
	{
		ChangeState(EnemyState::ATTACK);
	}
	else
	{
		MoveTowardsPlayer();
	}
}

void AEnemyBase::StateAttack()
{
	if (bIsAttacking) return;
	bIsAttacking = true;
	const float StartAttackDelay = FMath::RandRange(StartAttackDelayMin, StartAttackDelayMax);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemyBase::Attack, StartAttackDelay);
}

void AEnemyBase::StateStun()
{
}

void AEnemyBase::StateDead()
{
	if (GetCurrentMontage()) StopAnimMontage();
	bIsDead = true;
}

void AEnemyBase::Attack()
{
	bCanDeadDamage = true;
	if (AIController)
		AIController->StopMovement();
	const int RandomAttack = FMath::RandRange(0, M_Attack.Num() - 1);
	
	for (auto It = M_Attack.CreateConstIterator(); It; ++It)
	{
		if (It.GetId().AsInteger() == RandomAttack)
		{
			PlayAnimMontage(*It);
			break;
		}
	}
}

void AEnemyBase::ResetCanTakeDamage()
{
	bCanTakeDamage = true;
}

void AEnemyBase::ResetCanMove()
{
	bCanMove = true;
}

void AEnemyBase::MoveTowardsPlayer() const
{
	if(AIController)
	{
		FNavPathSharedPtr NavPath;
		FAIMoveRequest MoveRequest;

		MoveRequest.SetGoalActor(Player);
		MoveRequest.SetAcceptanceRadius(MoveToTargetRadius);
		AIController->MoveTo(MoveRequest, &NavPath);
	}
}

void AEnemyBase::AttackEnd()
{
	bCanDeadDamage = false;
	bIsAttacking = false;
	ChangeState(EnemyState::CHASE);
}

float AEnemyBase::FindPlayerDistance() const
{
	return  (Player)? FVector::Distance(GetActorLocation(), Player->GetActorLocation()) : 0;
}

#pragma endregion StateMachine
