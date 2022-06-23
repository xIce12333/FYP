// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KomachiAnimController.generated.h"

/**
 * 
 */
UCLASS(Transient, Blueprintable, HideCategories=(AnimInstance), BlueprintType)
class FYP_API UKomachiAnimController: public UAnimInstance
{
	GENERATED_BODY()
public:
	UKomachiAnimController();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void CheckMovement(AActor*);
	UPROPERTY(BlueprintReadOnly)
		bool isWalking;
};
