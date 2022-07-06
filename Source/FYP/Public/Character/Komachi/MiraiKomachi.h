// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KomachiStateManager.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MiraiKomachi.generated.h"

UCLASS()
class FYP_API AMiraiKomachi : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMiraiKomachi();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		struct FKomachiStateManager KomachiState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		class UStaticMeshComponent* Weapon;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
