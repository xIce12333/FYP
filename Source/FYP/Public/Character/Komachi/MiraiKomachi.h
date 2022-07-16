// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "GameFramework/Character.h"
#include "KomachiStateManager.h"
#include "Weapon.h"
#include "Components/InputComponent.h"
#include "EnemyBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MiraiKomachi.generated.h"

UCLASS()
class FYP_API AMiraiKomachi : public ACombatant
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMiraiKomachi();
	
	
	UPROPERTY(BlueprintReadOnly)
		bool bCanAttack;
	UPROPERTY(BlueprintReadOnly)
		bool bIsRolling;
	UPROPERTY(BlueprintReadOnly)
		bool bIsGuarding;
	UPROPERTY(BlueprintReadOnly)
		bool bGuardPressed;
	UPROPERTY(BlueprintReadOnly)
		bool bCanGuard;
	UPROPERTY(BlueprintReadOnly)
		bool bGuardE;
	UPROPERTY(BlueprintReadOnly)
		bool bGuardW;
	UPROPERTY(BlueprintReadOnly)
		bool bGuardNE;
	UPROPERTY(BlueprintReadOnly)
		bool bGuardNW;
	UPROPERTY(BlueprintReadOnly)
		bool bGuardSE;
	UPROPERTY(BlueprintReadOnly)
		bool bGuardSW;
	bool bIsInvulnerable;
	
	UPROPERTY(BlueprintReadOnly)
		float RunSpeed = 700;
	UPROPERTY(BlueprintReadOnly)
		float StrafeSpeed = 350;
	UPROPERTY(BlueprintReadOnly)
		float RollSpeed = 800;
	UPROPERTY(BlueprintReadOnly)
		float MeleeAttackSpeed = 800;
	UPROPERTY(BlueprintReadOnly)
		float KnockBackSpeed = 800;
	UPROPERTY(BlueprintReadOnly)
		FVector RollVec;

	bool CheckGuardSuccessful(const AEnemyBase* Enemy) const;
	void GuardSuccessful();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<UAnimMontage*> M_Attack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Roll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Hurt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Guard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_GuardSuccessful;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void EquipWeapon(AWeapon* Weapon);

	UPROPERTY(BlueprintReadOnly)
		AWeapon* WeaponEquipped;

	UFUNCTION()
	virtual void WeaponHitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	void ApplyDamage(float DamageAmount);
	void StopGuard();
private:
	void MoveForward(const float Axis);
	void MoveRight(const float Axis);
	UFUNCTION(BlueprintCallable)
		void Attack(FVector StickValue);
	
	void ToRunSpeed();
	void ToWalkSpeed();
	UFUNCTION(BlueprintCallable)
		void ToggleStrafe();
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
};
