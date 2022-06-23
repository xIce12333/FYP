// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KomachiStateManager.h"

/**
 * 
 */
class FYP_API KomachiBaseState
{
public:
	virtual void EnterState(class KomachiStateManager* KomachiSM) = 0;

	virtual void ChangeState(class KomachiStateManager* KomachiSM) = 0;
};
