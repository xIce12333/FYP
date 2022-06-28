// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MiraiKomachi.generated.h"

UCLASS()
class FYP_API AMiraiKomachi : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMiraiKomachi();

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void ToRunSpeed();
	void ToWalkSpeed();

	float WalkSpeed = 300;
	float RunSpeed = 700;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
