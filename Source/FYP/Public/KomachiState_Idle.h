// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KomachiStateManager.h"
#include "Character/Komachi/KomachiBaseState.h"

/**
 * 
 */
class FYP_API KomachiState_Idle : public KomachiBaseState
{
public:
	KomachiState_Idle();

	virtual void EnterState(class KomachiStateManager* komachiSM) override;

	virtual  void ChangeState(class KomachiStateManager* komachiSM) override;
};
