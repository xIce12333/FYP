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
		USphereComponent* DetectSphere;

	UPROPERTY(EditAnywhere)
		USphereComponent* CombatSphere;

	UPROPERTY(EditAnywhere)
		UBoxComponent* AttackHitBoxLeft;
	UPROPERTY(EditAnywhere)
		UBoxComponent* AttackHitBoxRight;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool bCanTakeDamage = true;
	
	// if player enters this range, enemy will start chasing the player
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")	
		float ChaseRange;

	// if player enters this range, enemy will start attacking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")	
		float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Die;
	AActor* Player;

	AAIController* AIController;
	
	virtual void TickStateMachine();
	virtual void ChangeState(const EnemyState NewState);
	virtual void StateIdle();
	virtual void StateChase();
	virtual void StateAttack();
	virtual void StateStun();
	virtual void StateDead();
	void ResetCanTakeDamage();
	void ResetCanMove();
	
	float FindDistance() const;		// Distance between enemy and player
};
