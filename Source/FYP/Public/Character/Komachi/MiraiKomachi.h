// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseClass/Combatant.h"
#include "GameFramework/Character.h"
#include "KomachiStateManager.h"
#include "Containers/Array.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MiraiKomachi.generated.h"

class APickableItem;
class AWeapon;
class AEnemyBase;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDied);

UCLASS()
class FYP_API AMiraiKomachi : public ACombatant
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMiraiKomachi();

	UPROPERTY(BlueprintAssignable)
		FPlayerDied PlayerDied;
	
	bool bCanAttack;
	bool bIsRolling;
	bool bIsGuarding;
	bool bGuardPressed;
	bool bCanGuard;
	bool bGuardE;
	bool bGuardW;
	bool bGuardNE;
	bool bGuardNW;
	bool bGuardSE;
	bool bGuardSW;
	bool bCanRoll;
	bool bIsInvulnerable;
	bool bCanPickItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RunSpeed = 700;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StrafeSpeed = 350;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RollSpeed = 800;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MeleeAttackSpeed = 800;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float KnockBackSpeed = 800;

	bool CheckGuardSuccessful(const AEnemyBase* Enemy) const;
	void GuardSuccessful();
	UFUNCTION(BlueprintImplementableEvent)
		void CameraShake();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* M_MeleeE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* M_MeleeW;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* M_MeleeSE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* M_MeleeSW;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* M_MeleeNE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* M_MeleeNW;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Roll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Hurt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_GuardLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_GuardLeftSuccessful;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_GuardRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_GuardRightSuccessful;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_PickUp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void PickUpItem();

	UPROPERTY(BlueprintReadOnly)
		AWeapon* WeaponEquipped;
	APickableItem* ItemPicking;

	UFUNCTION()
	virtual void WeaponHitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		class USphereComponent* EnemyDetectionCollider;
	void ApplyDamage(float DamageAmount);
	void StopGuard();
	UPROPERTY(BlueprintReadOnly)
		AActor* TargetEnemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TargetLockDistance = 800.0f;

	UFUNCTION(BlueprintCallable)
		void ToggleStrafe();
	TArray<class AActor*> NearbyEnemies;
	TArray<class AActor*> HitEnemies;

	UFUNCTION(BlueprintCallable)
		void BroadCastPlayerDied() { PlayerDied.Broadcast();}
private:
	void MoveForward(const float Axis);
	void MoveRight(const float Axis);
	UFUNCTION(BlueprintCallable)
		void Attack(FVector StickValue);
	
	void ToRunSpeed();
	void ToWalkSpeed();
	void ToggleGuard();
	void Roll();
	void MeleeN();
	void MeleeE();
	void MeleeS();
	void MeleeW();
	void MeleeNE();
	void MeleeNW();
	void MeleeSE();
	void MeleeSW();
	AActor* FindNearestEnemy();
	void CycleLeft();
	void CycleRight();
	void CycleEnemy(bool bLeft = true);
	void CameraRight(const float Axis);
	void CameraUp(const float Axis);
	
	UFUNCTION()
	void OnEnemyDetectionBeginOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEnemyDetectionEndOverlap(class UPrimitiveComponent*
			OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	
};

