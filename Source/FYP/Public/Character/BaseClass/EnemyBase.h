// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Combatant.h"
#include "Character/Komachi/MiraiKomachi.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"



#define ATTACK_SOCKET_LEFT "AttackSocketLeft"
#define ATTACK_SOCKET_RIGHT "AttackSocketRight"



UENUM(BlueprintType)
enum class EnemyState : uint8
{
	IDLE,
	CHASE,
	ATTACK,
	STUN,
	DEAD
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemyDied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyStun, bool, bIsStun);

class AMiraiKomachi;
UCLASS()
class FYP_API AEnemyBase : public ACombatant
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State Machine")
		EnemyState ActiveState;

	UPROPERTY(BlueprintAssignable)
		FEnemyDied EnemyDied;

	UPROPERTY(BlueprintAssignable)
		FEnemyStun EnemyStun;

	UPROPERTY(EditAnywhere)
		UBoxComponent* AttackHitBoxLeft;
	UPROPERTY(EditAnywhere)
		UBoxComponent* AttackHitBoxRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetComponent* LockOnCrosshair;

	UFUNCTION(BlueprintImplementableEvent)
		void SetCrosshair(bool bActive);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void ApplyDamage(float Damage);

	bool MeleeE;
	bool MeleeW;
	bool MeleeNE;
	bool MeleeNW;
	bool MeleeSE;
	bool MeleeSW;
	bool bIsStrongAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WanderSpeed = 150;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackSpeed = 700;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float KnockBackSpeed = 500;
	
	UPROPERTY(BlueprintReadOnly)
		bool bIsStunning;

		
	UFUNCTION()
		virtual void AttackHitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void AttackEnd();

	void FacePlayer();
	void HandleBeingGuarded();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool bIsInvulnerable;
	int RandomAttack;
	
	// if player enters this range, enemy will start chasing the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")	
		float ChaseRange = 800.0f;
	// if player enters this range, enemy will start attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")	
		float AttackRange = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Choke;
	AActor* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float StartAttackDelayMin = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float StartAttackDelayMax = 0.7f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveToTargetRadius = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		TSet<UAnimMontage*> M_Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float Damage = 10.0f;
	AAIController* AIController;
	
	FTimerHandle AttackTimer;
	FTimerHandle DisposeTimer;
	FTimerHandle StunTimer;
	
	virtual void TickStateMachine();
	virtual void ChangeState(const EnemyState NewState);
	virtual void StateIdle();
	virtual void StateChase();
	virtual void StateAttack();
	virtual void StateStun();
	virtual void StateDead();
	virtual void Attack();
	void MoveTowardsPlayer() const;
	float FindPlayerDistance() const;		// Distance between enemy and player
	void DisposeEnemy() {Destroy();}
	void ResetAttackBool();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxStunCount = 2;
	int CurrentStunCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StunTime = 3;
	bool CheckStun();
	void StunEnd();
	void HandleHitWeapon();
	void HandleHitPlayer(AMiraiKomachi* Target);
	void FindRandomPosition();

	UFUNCTION(BlueprintImplementableEvent)
		void AIWanderEvent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RandomMovementRadius = 1000;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector OriginPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bAIMoving = false;
};
