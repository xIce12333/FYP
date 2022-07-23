// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkeletonSoldier/SkeletonSoldier.h"

ASkeletonSoldier::ASkeletonSoldier()
{
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), "AttackSocketRight");
}

void ASkeletonSoldier::Attack()
{
	Super::Attack();
}

