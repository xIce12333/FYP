// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Combatant.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"


UENUM(BlueprintType)
enum class EnemyState : uint8
{
	IDLE,
	CHASE,
	ATTACK,
	STUN,
	DEAD
};

UCLASS()
class FYP_API AEnemyBase : public ACombatant
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State Machine")
		EnemyState ActiveState;

	UPROPERTY(EditAnywhere)
		UBoxComponent* AttackHitBoxLeft;
	UPROPERTY(EditAnywhere)
		UBoxComponent* AttackHitBoxRight;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void ApplyDamage(float Damage);

	bool MeleeE;
	bool MeleeW;
	bool MeleeNE;
	bool MeleeNW;
	bool MeleeSE;
	bool MeleeSW;
	float AttackSpeed = 700;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool bIsInvulnerable;
	
	// if player enters this range, enemy will start chasing the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")	
		float ChaseRange = 800.0f;
	// if player enters this range, enemy will start attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")	
		float AttackRange = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Die;
	
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

	
	UFUNCTION()
		virtual void AttackHitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
	
	FTimerHandle AttackTimer;
	FTimerHandle DisposeTimer;
	
	virtual void TickStateMachine();
	virtual void ChangeState(const EnemyState NewState);
	virtual void StateIdle();
	virtual void StateChase();
	virtual void StateAttack();
	virtual void StateStun();
	virtual void StateDead();
	virtual void Attack();
	void ResetCanMove();
	void MoveTowardsPlayer() const;

	UFUNCTION(BlueprintCallable)
		void AttackEnd();
	float FindPlayerDistance() const;		// Distance between enemy and player
	void FacePlayer();
	void DisposeEnemy();
	void ResetAttackBool();
};
