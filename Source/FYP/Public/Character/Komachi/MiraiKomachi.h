// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combatant.h"
#include "GameFramework/Character.h"
#include "KomachiStateManager.h"
#include "Weapon.h"
#include "Components/InputComponent.h"
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

#pragma region Boolean
	
	UPROPERTY(BlueprintReadOnly)
		bool bCanAttack = true;
	UPROPERTY(BlueprintReadOnly)
		bool bIsRolling = false;

#pragma endregion Boolean

#pragma region Speed
	
	UPROPERTY(BlueprintReadOnly)
		float RunSpeed = 700;
	UPROPERTY(BlueprintReadOnly)
		float StrafeSpeed = 350;
	UPROPERTY(BlueprintReadOnly)
		float RollSpeed = 800;
	UPROPERTY(BlueprintReadOnly)
		FVector RollVec;

#pragma endregion Speed

#pragma region Montage
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<UAnimMontage*> M_Attack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Roll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Animations)
		UAnimMontage* M_Hurt;

#pragma endregion Montage

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void EquipWeapon(AWeapon* Weapon);

	UPROPERTY(BlueprintReadOnly)
		AWeapon* WeaponEquipped;

private:
	void MoveForward(const float Axis);
	void MoveRight(const float Axis);
	UFUNCTION(BlueprintCallable)
		void Attack(FVector StickValue);
	
	void ToRunSpeed();
	void ToWalkSpeed();
	UFUNCTION(BlueprintCallable)
		void ToggleStrafe();
	
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
