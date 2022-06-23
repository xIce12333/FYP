// Fill out your copyright notice in the Description page of Project Settings.


#include "KomachiState_Idle.h"

KomachiState_Idle::KomachiState_Idle()
{
}

void KomachiState_Idle::EnterState(class KomachiStateManager* komachiSM)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
}

void KomachiState_Idle::ChangeState(class KomachiStateManager* komachiSM)
{
}

