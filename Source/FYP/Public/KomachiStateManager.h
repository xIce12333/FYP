// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KomachiState_Idle.h"

/**
 * 
 */
class FYP_API KomachiStateManager
{
public:
	KomachiStateManager();
	class KomachiBaseState* CurrentState;
	class KomachiState_Idle* IdleState;
	
};
