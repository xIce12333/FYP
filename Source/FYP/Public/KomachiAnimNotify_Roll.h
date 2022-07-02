// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Komachi/MiraiKomachi.h"
#include "KomachiAnimNotify_Roll.generated.h"


/**
 * 
 */
UCLASS()
class FYP_API UKomachiAnimNotify_Roll : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
private:
	static void HandleBeginRolling(AMiraiKomachi* Player);
	static void HandleFinishRolling(AMiraiKomachi* Player);
};
