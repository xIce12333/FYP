// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Character/Komachi/MiraiKomachi.h"
#include "KomachiAnimNotify_Roll.generated.h"


/**
 * 
 */
UCLASS()
class FYP_API UKomachiAnimNotify_Roll : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
private:
	static void HandleBeginRolling(AMiraiKomachi* Player);
	static void HandleFinishRolling(AMiraiKomachi* Player);
};
