// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Komachi/MiraiKomachi.h"
#include "KomachiAnimNotify_Hurt.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API UKomachiAnimNotify_Hurt : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
