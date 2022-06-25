// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Komachi/MiraiKomachi.h"
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
	
	UPROPERTY(BlueprintReadOnly)
		TMap<FString, bool> AnimState;

private:
	void ChangeAnimationState(const FString NewState);
	void CheckMovement(const AActor* OwningActor, const AMiraiKomachi* OwningCharacter);

};
