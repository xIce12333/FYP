// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Komachi/MiraiKomachi.h"
#include "KomachiStateManager.h"
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

	~UKomachiAnimController();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadOnly)
		bool bIsStrafing;
	UPROPERTY(BlueprintReadOnly)
		bool bIsDead;
	UPROPERTY(BlueprintReadOnly)
		float Speed;
	UPROPERTY(BlueprintReadOnly)
		float Direction;

private:
	void GetState(const AActor* OwningActor, const AMiraiKomachi* OwningCharacter);
};
