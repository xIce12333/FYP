// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseClass/EnemyBase.h"

#include <mutex>

#include "Blueprint/UserWidget.h"
#include "Character/Komachi/MiraiKomachi.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttackHitBoxLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitBoxLeft"));
	AttackHitBoxLeft->SetupAttachment(GetMesh(), ATTACK_SOCKET_LEFT);
	AttackHitBoxRight = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitBoxRight"));
	AttackHitBoxRight->SetupAttachment(GetMesh(), ATTACK_SOCKET_RIGHT);
	LockOnCrosshair = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnCrosshair"));
	LockOnCrosshair->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	ActiveState = EnemyState::IDLE;
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AIController = Cast<AAIController>(GetController());
	AttackHitBoxLeft->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::AttackHitBoxOnBeginOverlap);
	AttackHitBoxRight->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::AttackHitBoxOnBeginOverlap);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	CurrentHealth = MaxHealth;
	CurrentStunCount = MaxStunCount;
	bIsStunning = false;
	bIsInvulnerable = false;
}


// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickStateMachine();
}


void AEnemyBase::ApplyDamage(float DamageAmount)
{
	DamageAmount = (bIsStunning)? DamageAmount * 1.5 : DamageAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	CurrentDamage = DamageAmount;
	GenerateDamageText();
	if (CurrentHealth > 0) return;
	// enemy is dead
	if (GetCurrentMontage()) StopAnimMontage();
	if (AIController) AIController->StopMovement();
	ChangeState(EnemyState::DEAD);
	
}

void AEnemyBase::AttackHitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (bCanDealDamage)
	{
		AMiraiKomachi* Target = Cast<AMiraiKomachi>(OtherActor);
		
		if (OtherActor->ActorHasTag("PlayerWeapon") && !bIsStrongAttack)		// Enemy hits player's weapon
		{
			HandleHitWeapon();
			return;
		}
		else if (Target)		// Enemy hits player
		{
			HandleHitPlayer(Target);
		}
	} 
}

void AEnemyBase::HandleHitWeapon()
{
	AMiraiKomachi* Komachi = Cast<AMiraiKomachi>(Player);
	if (Komachi && Komachi->CheckGuardSuccessful(this))
	{
		bCanDealDamage = false;
		Komachi->GuardSuccessful();
		if (GetCurrentMontage()) StopAnimMontage();
		if (!CheckStun() && M_Choke)		
		{
			LaunchCharacter(-GetActorRotation().Vector()* KnockBackSpeed, true, true);
			PlayAnimMontage(M_Choke);
		}
		else
			ChangeState(EnemyState::STUN);
	}
}

void AEnemyBase::HandleHitPlayer(AMiraiKomachi* Target)
{
	bCanDealDamage = false;
	if (!bIsStrongAttack && Target->CheckGuardSuccessful(this))
	{
		Target->GuardSuccessful();
		if (GetCurrentMontage()) StopAnimMontage();
		if (!CheckStun() && M_Choke)		
		{
			PlayAnimMontage(M_Choke);
		}
		else
			ChangeState(EnemyState::STUN);
	}
	else 
	{
		const float MinDamage = Damage * 0.9;
		const float MaxDamage = Damage * 1.1;
		Target->ApplyDamage(static_cast<int>(FMath::RandRange(MinDamage, MaxDamage)));
	}
}


bool AEnemyBase::CheckStun()
{
	--CurrentStunCount;
	UE_LOG(LogTemp, Warning, TEXT("StunC: %d"), CurrentStunCount);
	if (CurrentStunCount <= 0)
	{
		CurrentStunCount = MaxStunCount;
		return true;
	}
	return false;
}

void AEnemyBase::StunEnd()
{
	bIsStunning = false;
	EnemyStun.Broadcast(false);
	AttackEnd();
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
	else if (PlayerDistance < ChaseRange)
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
	if (AIController) AIController->StopMovement();
	bIsAttacking = true;
	FacePlayer();
	const float StartAttackDelay = FMath::RandRange(StartAttackDelayMin, StartAttackDelayMax);
	RandomAttack =  FMath::RandRange(0, M_Attack.Num() - 1);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemyBase::Attack, StartAttackDelay);
}

void AEnemyBase::StateStun()
{
	if (bIsStunning) return;
	bIsStunning = true;
	EnemyStun.Broadcast(true);
	GetWorldTimerManager().SetTimer(StunTimer, this, &AEnemyBase::StunEnd, StunTime);
}

void AEnemyBase::StateDead()
{
	if (GetCurrentMontage()) StopAnimMontage();
	GetWorld()->GetTimerManager().SetTimer(DisposeTimer, this, &AEnemyBase::DisposeEnemy, 5.0f);
	bIsDead = true;
	EnemyDied.Broadcast();
	SetCrosshair(false);
	bCanDealDamage = false;
	AMiraiKomachi* Komachi = Cast<AMiraiKomachi>(Player);
	if (Komachi)
	{
		Komachi->NearbyEnemies.Remove(this);
		Komachi->ToggleStrafe();
		Komachi->ToggleStrafe();
	}
}

#pragma endregion StateMachine

void AEnemyBase::Attack()
{
	bCanDealDamage = true;
	if (AIController)
		AIController->StopMovement();
	switch (RandomAttack)
	{
	case 0:
		MeleeE = true;
		UE_LOG(LogTemp, Warning, TEXT("E Attack!"));
		break;
	case 1:
		MeleeNE = true;
		UE_LOG(LogTemp, Warning, TEXT("NE Attack!"));
		break;
	case 2:
		UE_LOG(LogTemp, Warning, TEXT("NW Attack!"));
		MeleeNW = true;
		break;
	case 3:
		MeleeSE = true;
		UE_LOG(LogTemp, Warning, TEXT("SE Attack!"));
		break;
	case 4:
		MeleeSW = true;
		UE_LOG(LogTemp, Warning, TEXT("SW Attack!"));
		break;
	case 5:
		MeleeW = true;
		UE_LOG(LogTemp, Warning, TEXT("W Attack!"));
	}
	
	for (auto It = M_Attack.CreateConstIterator(); It; ++It)
	{
		if (It.GetId().AsInteger() == RandomAttack)
		{
			PlayAnimMontage(*It);
			break;
		}
	}
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
	bCanDealDamage = false;
	bIsAttacking = false;
	ResetAttackBool();
	ChangeState(EnemyState::CHASE);
}

float AEnemyBase::FindPlayerDistance() const
{
	return  (Player)? FVector::Distance(GetActorLocation(), Player->GetActorLocation()) : 0;
}

void AEnemyBase::FacePlayer()
{
	if (!Player) return;
	FVector Direction = Player->GetActorLocation() - GetActorLocation();
	Direction = FVector(Direction.X, Direction.Y, 0);
	const FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorRotation(Rotation);
}

void AEnemyBase::ResetAttackBool()
{
	MeleeE = false;
	MeleeW = false;
	MeleeNE = false;
	MeleeNW = false;
	MeleeSE = false;
	MeleeSW = false;
}
