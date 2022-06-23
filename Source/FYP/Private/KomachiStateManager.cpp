// Fill out your copyright notice in the Description page of Project Settings.


#include "KomachiStateManager.h"

KomachiStateManager::KomachiStateManager()
{
	IdleState = new KomachiState_Idle();
	CurrentState = IdleState;
	CurrentState->EnterState(this);
	
}

